/* 
 * File:   CoordStructs.h
 * Author: Akela1101
 *
 * Created on 20 Март 2011 г., 12:05
 */

#ifndef _COORDSTRUCTS_H
#define	_COORDSTRUCTS_H


namespace Strategix
{
	struct MapCoord
	{
		int x, y;

		MapCoord() {}

		MapCoord(int x, int y) : x(x), y(y)
		{
		}

		bool operator ==(const MapCoord &right) const
		{
			return x == right.x && y == right.y;
		}

		bool operator !=(const MapCoord &right) const
		{
			return x != right.x || y != right.y;
		}

		MapCoord operator +(const MapCoord &right) const
		{
			MapCoord ret(x + right.x, y + right.y);
			return ret;
		}
	};
}

#endif	/* _COORDSTRUCTS_H */

