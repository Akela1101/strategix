/* 
 * File:   GameStructs.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 19:44
 */

#ifndef _GAMESTRUCTS_H
#define	_GAMESTRUCTS_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace Strategix
{
	using namespace std;

// EntityInfo
	typedef int HpType;
	typedef float SpeedType;
	typedef int SingleResType;
	typedef map<string, SingleResType> ResType;
	typedef vector<string> Names;

	struct Params
	{		
		HpType hp;		
		SpeedType speed;
	};
// **********

	struct MapCoord
	{
		int x, y;

		MapCoord() { x = 0; y = 0; }
		MapCoord(int x, int y)
		{
			this->x = x;
			this->y = y;
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

	enum PlayerType
	{
		HUMAN,
		AI,
		NET
	};
}

#endif	/* _GAMESTRUCTS_H */

