/* 
 * File:   Map.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 17:54
 */

#ifndef _MAP_H
#define	_MAP_H

#include "MapResource.h"

#include <list>

#include "Strategix_Forward.h"


namespace Strategix
{
	using namespace std;

	class Map
	{
	public:
		struct Cell
		{
			int terrainType;
			float retard; // defines from terrain type
			mutable sh_p<MapResource> mapResource;
			//mutable list<Enti*> entis;
		};

	protected:
		string name;
		int width, length;
		sh_a<sh_a<Cell> > cells; // [rows][columns] (i.e. [y][x])
			
	public:
		virtual ~Map() {}

		const string &GetName() const { return name; }
		const int GetWidth() const { return width; }
		const int GetLength() const { return length; }
		const Cell &GetCell(const int x, const int y) const	{ return cells[y][x]; }
		const Cell &GetCell(const MapCoord mc) const { return cells[mc.y][mc.x]; }

		virtual float PickResource(sh_p<MapResource> mapResource, const float amount) = 0;

		bool IsCell(const MapCoord &mc) const
		{
			return ( mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length ) ? false : true;
		}
	};	
}

#endif	/* _MAP_H */

