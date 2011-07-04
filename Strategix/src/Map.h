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
			mutable list<Enti*> entis;
		};

	protected:
		string name;
		int width, length;
		Cell **cells; // [rows][columns] (i.e. [y][x])
			
	public:
		virtual ~Map() {}

		const string &GetName() const { return name; }
		const int GetWidth() const { return width; }
		const int GetLength() const { return length; }
		const Cell &GetCell(const int x, const int y) const	{ return cells[y][x]; }
		const Cell &GetCell(const MapCoord mc) const { return cells[mc.y][mc.x]; }
		const float GetResource(sh_p<MapResource> mapResource, const float amount)
		{
			if( mapResource->resource >= amount )
			{
				mapResource->resource -= amount;
				return amount;
			}
			else // remove resource
			{
				const float remain = mapResource->resource;
				mapResource->resource -= remain;
				mapResource.reset();
				return remain;
			}
		}

		bool IsCell(const MapCoord &mc) const
		{
			return ( mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length ) ? false : true;
		}
	};	
}



#endif	/* _MAP_H */

