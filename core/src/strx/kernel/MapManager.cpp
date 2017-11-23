#include <fstream>
#include <algorithm>
#include <deque>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <strx/kernel/Kernel.h>
#include <strx/map/Map.h>
#include <strx/map/Mine.h>
#include <strx/player/Player.h>

#include "MapManager.h"


namespace strx
{
namespace fs = boost::filesystem;

MapManager::MapManager(const string& mapName)
		: mapName(mapName)
		, baseMap(new BaseMap())
{
	const string& fileName = GetFilePath(mapName);
	ifstream fin(fileName.c_str());
	
	string cString;
	getline(fin, cString); // top string
	getline(fin, cString); // version
	
	// Map Content
	fin >> baseMap->width >> baseMap->length;
	if (baseMap->width > 1000 || baseMap->length > 1000)
	{
		nya_throw << "Map size is too large: %dx%d."s % baseMap->width % baseMap->length;
	}
	
	baseMap->cells.resize(baseMap->length);
	umultimap<int, float&> type_retards;
	for (int j = 0; j < baseMap->length; ++j)
	{
		baseMap->cells[j].resize(baseMap->width);
		for (int i = 0; i < baseMap->width; ++i)
		{
			if (fin.good())
			{
				Cell& cell = baseMap->cells[j][i];
				fin >> cell.terrainType;
				type_retards.emplace(cell.terrainType, cell.retard); // +M
			}
			else
			{
				nya_throw << "Wrong map format in file: " << fileName;
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
	fin >> playersNumber;
	for (int iPlayer = playersNumber; iPlayer; --iPlayer)
	{
		MapCoord coord;
		fin >> coord.x >> coord.y;
		initialPositions.push_back(coord);
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
		baseMap->cells[j][i].mine = mine;
		mines.emplace(mine, mine);
	}
	
	fin.close();
}

MapManager::~MapManager() = default;

u_p<Map> MapManager::CreateMap(Player& player)
{
	return make_u<Map>(*baseMap, player, initialPositions[player.GetId()]);
}

void MapManager::RemoveResource(Mine* mine)
{
	baseMap->GetCell(mine->mapCoord).mine = nullptr;
	mines.erase(mine);
}

string MapManager::GetFilePath(const string& name) const
{
	auto fileName = boost::str(boost::format("%s.map") % name);
	return (fs::path(Kernel::GetMapsDir()) / fileName).string();
}

}
