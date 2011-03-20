/* 
 * File:   Map.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 17:54
 */

#ifndef _MAP_H
#define	_MAP_H

#include "CoordStructs.h"
#include "StrategixError.h"

#include <string>
#include <map>
#include <deque>
#include <list>
#include <vector>


namespace Strategix
{
	using namespace std;
	
	class Map
	{
	public:
		struct Cell
		{
			short terrType;
			float retard; // defines from terrain type
			float highness;

			// for search..
			MapCoord mc;
			typedef int Price;
			Price F, G, H;
			Cell *parent;
		};

		// Description of terrain type
		struct Terrain
		{
			string name;
			float retard;

			Terrain() {}
			Terrain(const Terrain &copy)
			{
				this->name = copy.name;
				this->retard = copy.retard;
			}
			Terrain(const string &name, const float &retard)
			{
				this->name = name;
				this->retard = retard;
			}
		};
		// map[terrType, Terrain]
		typedef map<short, Terrain> TerrainTypes;	

	private:
		static TerrainTypes terrains;

		string name;
		int width, length, nPlayers;
		mutable Cell **cells; // [rows][columns] (i.e. [y][x])

	public:
		vector<MapCoord> initialPositions;

	public:
		static const Terrain &GetTerrain(const short terrType) { return terrains[terrType]; }

		Map(const string name);
		
		const int &GetWidth() const { return width; }
		const int &GetLength() const { return length; }
		const Cell &operator ()(const int x, const int y) const { return cells[y][x]; }
				
		void OutMatrix() const;

		bool IsIn(const list<Cell*> &list, const Cell *cell) const;
		bool IsAccessible(const MapCoord &mc) const;
		int Distance(const MapCoord &a, const MapCoord &b) const;
		deque<MapCoord> *BuildWay(const MapCoord &from, const MapCoord &till) const;

		deque<MapCoord> *BuildWay_Debug(const MapCoord &from, const MapCoord &till, list<Cell*> *&p_closed) const;

	private:
		static bool LoadTerrains();		

		static const string GetFilePath(const string name);

		inline Cell *getCell(const MapCoord &mc) const
		{
			if( mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length )
				return 0;
			return &cells[mc.y][mc.x];
		}

	};	
}



#endif	/* _MAP_H */

