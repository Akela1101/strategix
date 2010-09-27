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
	
	struct Resources
	{
		typedef int ResType;
		map<string, ResType > res;
	};

	struct Params
	{
		typedef int HpType;
		HpType hp;
		typedef float SpeedType;
		SpeedType speed;
	};

	typedef vector<string> Names;

	struct GameSets
	{
		set<string> raceSet;
		set<string> entKindSet;
		set<string> resourcesSet;
	};

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

	struct PlayerInitial
	{
		PlayerType playerType;
		int mapPos;
		string raceName;
	};
}

#endif	/* _GAMESTRUCTS_H */

