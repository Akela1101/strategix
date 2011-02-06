/* 
 * File:   Map.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 17:54
 */

#include "Map.h"
#include "Log.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <deque>
#include <list>
#include <string>


using namespace Strategix;
using namespace std;

Map::TerrainTypes Map::terrains;

bool Map::LoadTerrains()
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

const string Map::GetFilePath(const string name)
{
	string mapPath = "Maps/";
	mapPath += name + ".map";
	return mapPath;
}

Map::Map(const string name)
{
	if( !terrains.size() )
	{
		if( !LoadTerrains() )
		{
			throw STRATEGIX_ERROR("Wrong terrains.def");
		}
	}

	const string &fileName = GetFilePath(name);
	ifstream fin(fileName.c_str());

	char cString[101];
	fin.getline(cString, 100); // mapFileTopString
	fin.getline(cString, 100); // terrainsDefinitionFileName

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
				fin >> cell.terrType;
				cell.mc = MapCoord(i, j);
				cell.retard = terrains[cell.terrType].retard;
			}
			else
			{
				throw STRATEGIX_ERROR((string("Wrong map format in file: ") + fileName).c_str());
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

void Map::OutMatrix() const
{
	cout << endl << endl;

	for( int i = 0; i < length; ++i )
	{
		for( int j = 0; j < width; ++j )
		{
			cout << cells[i][j].terrType << " ";
		}
		cout << endl;
	}
}

bool Map::IsIn(const list<Cell*> &list, const Cell *cell) const
{
	return list.end() != find(list.begin(), list.end(), cell);
}

bool Map::IsAccessible(const MapCoord &mc) const
{
	if( terrains[ cells[mc.y][mc.x].terrType ].retard <= 0 ) // water or mount
		return false;
	return true;
}

int Map::Distance(const MapCoord &a, const MapCoord &b) const
{
	return (abs(a.x - b.x) + abs(a.y - b.y)) * 10;
}

deque<MapCoord> *Map::BuildWay(const MapCoord &from, const MapCoord &till) const
{
	list<Cell*> *p_closed = 0;
	deque<MapCoord> *way = BuildWay_Debug(from, till, p_closed);
	delete p_closed;

	return way;
}

deque<MapCoord> *Map::BuildWay_Debug(const MapCoord &from, const MapCoord &till, list<Cell*> *&p_closed) const
{
	deque<MapCoord> *way = new deque<MapCoord>();

	list<Cell*> opened;
	delete p_closed; p_closed = new list<Cell*>();
	list<Cell*> &closed = *p_closed;

	Cell *current, *checking;

	if( from.x == till.x && from.y == till.y )
		return way;

	static const MapCoord around[8] =
	{
		MapCoord(-1,  1), MapCoord( 0, 1), MapCoord( 1, 1),
		MapCoord(-1,  0), MapCoord( 1,-1), MapCoord( 1, 0),
		MapCoord(-1, -1), MapCoord( 0,-1) // <^ done for ability % 2
	};

	//
	current = getCell(from);
	current->parent = current;
	current->G = current->H = current->F = 0;

	opened.push_back(current);

	bool is_found = false;
	while( !opened.empty() )
	{
		list<Cell*>::iterator it_min, it = opened.begin();
		it_min = it++;
		Cell::Price F_min = (*it_min)->F;
		
		for( ; it != opened.end(); ++it )
		{
			if( F_min > (*it)->F )
			{
				it_min = it;
				F_min = (*it)->F;
			}
		}
		opened.erase(it_min);
		current = *it_min;
		closed.push_front(current);

		// Tsuite kita desu
		if( current->mc == till )
		{
			is_found = true;
			// Return list
			Cell *from_cell = getCell(from);
			for( ;current != from_cell; current = current->parent )
			{
				way->push_front(current->mc);
			}
			way->push_front(current->mc);

			break;
		}	

		for( int i = 0; i < 8; ++i )
		{
			MapCoord checking_mc = current->mc + around[i];

			checking = getCell(checking_mc);
			if( !checking || IsIn(closed, checking) || !IsAccessible(checking_mc) )
				continue;

			Cell::Price new_G = current->G + ((i % 2) ? 10 : 14) * current->retard; // sqrt(2)*10, 10

			if( !IsIn(opened, checking) )
			{
				checking->parent = current;
				checking->G = new_G;
				checking->H = Distance(checking->mc, till);
				checking->F = checking->G + checking->H;
				opened.push_back(checking);
			}
			else
			{
				// in open list & mark < old mark
				if( checking->G > new_G )
				{
					checking->parent = current;
					checking->G = new_G;
					checking->F = checking->G + checking->H;
				}
			}
		}
	}

	return way;
}
