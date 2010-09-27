/* 
 * File:   Map.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 17:54
 */

#ifndef _MAP_H
#define	_MAP_H

#include "GameStructs.h"
#include "StraxSingleton.h"
#include "Exception.h"

#include <string>
#include <map>
#include <deque>
#include <list>

namespace Strategix
{
	using namespace std;
	
	class Map : public StraxSingleton<Map>
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
		// Map[terrType, Terrain]
		typedef map<short, Terrain> TerrainTypes;	

	private:
		string name;
		int width, length, nPlayers;
		Cell **cells; // [rows][columns] (i.e. [y][x])
		TerrainTypes terrains;
		vector<MapCoord> initialPositions;

	public:
		const int &GetWidth() const { return width; }
		const int &GetLength() const { return length; }
		const Cell &operator ()(const int x, const int y) const { return cells[y][x]; }
		const Terrain &GetTerrain(const short terrType) { return terrains[terrType]; } // cannot be const because of map.[]

		void InitFromTextFile(string file_name) throw(StraxError);
		void OutMatrix();

		bool IsIn(const list<Cell*> &list, const Cell *cell) const;
		bool IsAccessible(const MapCoord &mc);
		int Distance(const MapCoord &a, const MapCoord &b) const;
		deque<MapCoord> *BuildWay(const MapCoord &from, const MapCoord &till);

		deque<MapCoord> *BuildWay_Debug(const MapCoord &from, const MapCoord &till, list<Cell*> *&p_closed);

	private:
		inline Cell *getCell(const MapCoord &mc)
		{
			if( mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length )
				return 0;
			return &cells[mc.y][mc.x];
		}

	};
}



#endif	/* _MAP_H */

