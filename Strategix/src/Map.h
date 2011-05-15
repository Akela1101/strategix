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
#include "StrategixCommon.h"
#include "Nya.hpp"


namespace Strategix
{	
	class Map
	{
	public:
		struct Resource
		{
			ResType resType;
			float amount;

			Resource(const ResType resType, const float amount)
				: resType(resType), amount(amount) {}
		};

		struct Cell
		{
			int terrainType;
			float retard; // defines from terrain type
			sh_p<Resource> resource;
		};

	protected:
		string name;
		int width, length;
		Cell **cells; // [rows][columns] (i.e. [y][x])
			
	public:		
		const string &GetName() const { return name; }
		const int GetWidth() const { return width; }
		const int GetLength() const { return length; }
		const Cell &operator ()(const int x, const int y) const	{ return cells[y][x]; }
		const Cell &operator ()(const MapCoord mc) const { return cells[mc.y][mc.x]; }

		bool IsCell(const MapCoord &mc) const
		{
			return ( mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length ) ? false : true;
		}
	};	
}



#endif	/* _MAP_H */

