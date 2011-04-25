/* 
 * File:   MapFull.cpp
 * Author: Akela1101
 * 
 * Created on 24 Март 2011 г., 14:02
 */

#include "Log.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <deque>
#include <string>

#include "MapFull.h"


namespace Strategix
{
	using namespace std;

MapFull::MapFull(const string &name)
{
	if( !LoadTerrains() )
	{
		STRATEGIX_ERROR("Wrong terrains.def");
	}

	const string &fileName = GetFilePath(name);
	ifstream fin(fileName.c_str());

	char cString[101];
	fin.getline(cString, 100); // top string
	fin.getline(cString, 100); // terrains.def

	// Name
	fin.getline(cString, 100);
	this->name = cString;

	// Map Content
	fin >> width >> length;

	cells = new Cell*[length];
	for( int j = 0; j < length; ++j )
	{
		cells[j] = new Cell[width];
		for( int i = 0; i < width; ++i )
		{
			if( fin.good() )
			{
				Cell &cell = cells[j][i];
				//cell.mc = MapCoord(i, j);

				fin >> cell.terrType;
				cell.retard = terrains[cell.terrType].retard;
			}
			else
			{
				STRATEGIX_ERROR(string("Wrong map format in file: ") + fileName);
			}
		}
	}

	// Initial Positions
	fin >> nPlayers;

	MapCoord mc;
	for( int iPlayer = 0; iPlayer < nPlayers; ++iPlayer )
	{
		fin >> mc.x >> mc.y;
		initialPositions.push_back(mc);
	}

	// Добавь чтение объектов же!

	fin.close();
}

MapFull::~MapFull()
{
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

	if( nTypes <= 0)
		return false;

	string type;
	float retard;
	for( short n = 0; n < nTypes; ++n )
	{
		fdesc >> retard >> type;

		terrains[n] = Terrain(type, retard);
	}
	fdesc.close();
	return true;
}

}
