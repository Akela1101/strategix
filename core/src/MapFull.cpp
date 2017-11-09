/* 
 * File:   MapFull.cpp
 * Author: Akela1101
 * 
 * Created on 24 Март 2011 г., 14:02
 */

#include "MapResource.h"
#include "MapLocal.h"

#include <fstream>
#include <algorithm>
#include <deque>

#include "MapFull.h"


namespace Strategix
{
using namespace std;

MapFull::MapFull(const string& name)
{
	if (!LoadTerrains())
	{
		STRATEGIX_EXCEPTION("Wrong terrains.def");
	}
	
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
				STRATEGIX_EXCEPTION("Wrong map format in file: " + fileName);
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
		
		const Resource resource = KernelBase::GS().MakeResource(resourceName, initialAmount);
		cells[j][i].mapResource.reset(new MapResource(resource, MapCoord(i, j)));
	}
	
	fin.close();
}

bool MapFull::LoadTerrains()
{
	ifstream fdesc("Maps/terrains.def");
	char cString[100];
	fdesc.getline(cString, 100);
	
	// Terrain Name and Retard
	int nTypes = -1;
	fdesc >> nTypes;
	nTypes *= nTypes; // nTypes^2
	
	if (nTypes <= 0)
		return false;
	
	string type;
	float retard;
	for (int n = 0; n < nTypes; ++n)
	{
		fdesc >> retard >> type;
		
		terrains[n] = Terrain(type, retard);
	}
	fdesc.close();
	return true;
}

s_p<MapLocal> MapFull::CreateMapLocal(Player* player)
{
	s_p<MapLocal> mapLocal(new MapLocal(player, this));
	mapLocals.push_back(mapLocal);
	return mapLocal;
}

float MapFull::PickResource(s_p<MapResource> mapResource, const float amount)
{
	if (mapResource->resource > amount)
	{
		mapResource->resource -= amount;
		return amount;
	}
	else
	{
		s_p<MapResource>& mapResourceOnMap = GetCell(mapResource->mapCoord).mapResource;
		if (!mapResourceOnMap)
		{
			return 0;
		}
		else // remove resource
		{
			const float remain = mapResource->resource;
			mapResource->resource -= remain;
			for (auto& mapLocal : mapLocals)
			{
				mapLocal->RemoveMapResource(mapResource);
			}
			mapResourceOnMap.reset();
			return remain;
		}
	}
}

}
