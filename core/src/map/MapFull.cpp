#include "Mine.h"
#include "MapLocal.h"

#include <fstream>
#include <algorithm>
#include <deque>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include "MapFull.h"


namespace strategix
{
using namespace std;
namespace fs = boost::filesystem;

MapFull::MapFull(const string& name)
{
	this->name = name;
	
	const string& fileName = GetFilePath(name);
	ifstream fin(fileName.c_str());
	
	char cString[1001];
	fin.getline(cString, 1000); // top string
	fin.getline(cString, 1000); // version
	
	// Map Content
	fin >> width >> length;
	if (width > 1000 || length > 1000)
	{
		throw_nya << "Map size is too large: %dx%d."s % width % length;
	}
	
	cells.resize(length);
	umultimap<int, float&> type_retards;
	for (int j = 0; j < length; ++j)
	{
		cells[j].resize(width);
		for (int i = 0; i < width; ++i)
		{
			if (fin.good())
			{
				Cell& cell = cells[j][i];
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
	fin >> nTypes;
	for (int n = 0; n < nTypes; ++n)
	{
		int terrainType;
		string terrainName;
		float retard;
		fin >> terrainType >> terrainName >> retard;
		
		terrains[n] = Terrain(terrainName, retard);
		
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
		cells[j][i].mine.reset(new Mine(move(resource), MapCoord(i, j)));
	}
	
	fin.close();
}

u_p<MapLocal> MapFull::CreateMapLocal(Player* player)
{
	return make_u<MapLocal>(player, this);
}

float MapFull::PickResource(Mine* mine, float amount)
{
	if (*mine->resource > amount)
	{
		*mine->resource -= amount;
		return amount;
	}
	else
	{
		s_p<Mine>& mineOnMap = GetCell(mine->mapCoord).mine;
		if (!mineOnMap)
		{
			return 0;
		}
		else // remove resource
		{
			float remain = *mine->resource;
			*mine->resource -= remain;
//			for (auto&& mapLocal : mapLocals)
//			{
//				mapLocal->RemoveMine(mine);
//			}
			mineOnMap.reset();
			return remain;
		}
	}
}

string MapFull::GetFilePath(const string& name) const
{
	auto fileName = boost::str(boost::format("%s.map") % name);
	return (fs::path(Kernel::GetMapsDir()) / fileName).string();
}

}
