#include <fstream>
#include <algorithm>
#include <deque>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <Kernel.h>
#include <map/Map.h>
#include <map/Mine.h>

#include "MapManager.h"


namespace strategix
{
namespace fs = boost::filesystem;

MapManager::MapManager(const string& mapName)
		: mapName(mapName)
		, map(new Map(this))
{
	const string& fileName = GetFilePath(mapName);
	ifstream fin(fileName.c_str());
	
	string cString;
	getline(fin, cString); // top string
	getline(fin, cString); // version
	
	// Map Content
	fin >> map->width >> map->length;
	if (map->width > 1000 || map->length > 1000)
	{
		throw_nya << "Map size is too large: %dx%d."s % map->width % map->length;
	}
	
	map->cells.resize(map->length);
	umultimap<int, float&> type_retards;
	for (int j = 0; j < map->length; ++j)
	{
		map->cells[j].resize(map->width);
		for (int i = 0; i < map->width; ++i)
		{
			if (fin.good())
			{
				Cell& cell = map->cells[j][i];
				fin >> cell.terrainType;
				type_retards.emplace(cell.terrainType, cell.retard); // +M
			}
			else
			{
				throw_nya << "Wrong map format in file: " << fileName;
			}
		}
	}
	
	// Terrain descriptions
	int nTypes = 0;
	umap<int, pair<string, float>> terrains;
	fin >> nTypes;
	for (int n = 0; n < nTypes; ++n)
	{
		int terrainType;
		string terrainName;
		float retard;
		fin >> terrainType >> terrainName >> retard;
		
		terrains[n] = { terrainName, retard };
		
		for (auto&& type_retard : make_ir(type_retards.equal_range(terrainType)))
		{
			type_retard.second = retard; // R
		}
	}
	
	// Initial Positions
	fin >> nPlayers;
	for (int iPlayer = nPlayers; iPlayer; --iPlayer)
	{
		MapCoord mc;
		fin >> mc.x >> mc.y;
		initialPositions.push_back(mc);
	}
	
	// Resources
	int nResources = 0;
	fin >> nResources;
	for (int iRes = nResources; iRes; --iRes)
	{
		int i, j;
		string resourceName;
		float initialAmount;
		fin >> i >> j >> resourceName >> initialAmount;
		
		auto resource = Kernel::MakeResource(resourceName, initialAmount);
		auto mine = new Mine(move(resource), MapCoord(i, j));
		map->cells[j][i].mine = mine;
		mines.emplace(mine, mine);
	}
	
	fin.close();
}

MapManager::~MapManager() = default;

u_p<Map> MapManager::CreateMap(Player* player)
{
	return make_u<Map>(this); //TODO: local map
}

void MapManager::RemoveResource(Mine* mine)
{
	map->GetCell(mine->mapCoord).mine = nullptr;
	mines.erase(mine);
}

string MapManager::GetFilePath(const string& name) const
{
	auto fileName = boost::str(boost::format("%s.map") % name);
	return (fs::path(Kernel::GetMapsDir()) / fileName).string();
}

}
