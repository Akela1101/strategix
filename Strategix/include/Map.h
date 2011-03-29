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


namespace Strategix
{	
	class Map
	{
	protected:
		struct Cell
		{
			short terrType;
			float retard; // defines from terrain type	
		};

	protected:
		string name;
		int width, length;
		Cell **cells; // [rows][columns] (i.e. [y][x])

	public:		
		const int GetWidth() const { return width; }
		const int GetLength() const { return length; }

		// ??????
		Cell *getCell(const MapCoord &mc) const
		{
			if( mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length )
				return 0;
			return &cells[mc.y][mc.x];
		}

	public:
		const Cell &operator ()(const int x, const int y) const
		{
			return cells[y][x];
		}
	};	
}



#endif	/* _MAP_H */

