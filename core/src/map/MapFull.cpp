#include "Mine.h"
#include "MapLocal.h"

#include <fstream>
#include <algorithm>
#include <deque>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

#include "MapFull.h"


namespace strategix
{
using namespace std;
namespace fs = boost::filesystem;

MapFull::MapFull(const string& name)
{
	LoadTerrains();
	
	const string& fileName = GetFilePath(name);
	ifstream fin(fileName.c_str());
	
	char cString[101];
	fin.getline(cString, 100); // top string
	fin.getline(cString, 100); // terrains.def
	
	// Name
	fin.getline(cString, 100);
	this->name = cString;
	
	// Map Content
	fin >> width >> length;
	
	cells.resize(length);
	for (int j = 0; j < length; ++j)
	{
		cells[j].resize(width);
		for (int i = 0; i < width; ++i)
		{
			if (fin.good())
			{
				Cell& cell = cells[j][i];
				fin >> cell.terrainType;
				cell.retard = terrains[cell.terrainType].retard;
			}
			else
			{
				throw_nya("Wrong map format in file: " + fileName);
			}
		}
	}
	
	// Initial Positions
	MapCoord mc;
	
	fin >> nPlayers;
	for (int iPlayer = nPlayers; iPlayer; --iPlayer)
	{
		fin >> mc.x >> mc.y;
		initialPositions.push_back(mc);
	}
	
	// Resources
	int nResources, i, j;
	string resourceName;
	float initialAmount;
	
	fin >> nResources;
	for (int iRes = nResources; iRes; --iRes)
	{
		fin >> i >> j >> resourceName >> initialAmount;
		
		// @#~ проверять правильность входных параметров!!!
		
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

void MapFull::LoadTerrains()
{
	const string& filePath = "maps/terrains.def"; //TODO: should be inside each *.map
	
	ifstream definitionFile(filePath);
	if (definitionFile.rdstate() & ios::failbit)
	{
		throw_nya("Wrong path: " + filePath);
	}
	
	char cString[100];
	definitionFile.getline(cString, 100);
	
	// Terrain Name and Retard
	int nTypes = -1;
	definitionFile >> nTypes;
	nTypes *= nTypes; // nTypes^2
	
	if (nTypes <= 0)
	{
		throw_nya("Wrong format of " + filePath);
	}
	
	string type;
	float retard;
	for (int n = 0; n < nTypes; ++n)
	{
		definitionFile >> retard >> type;
		
		terrains[n] = Terrain(type, retard);
	}
	definitionFile.close();
}

string MapFull::GetFilePath(const string& name) const
{
	auto fileName = boost::str(boost::format("%s.map") % name);
	return (fs::path(Kernel::GetMapsDir()) / fileName).string();
}

}
