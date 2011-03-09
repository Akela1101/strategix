/* 
 * File:   Game.h
 * Author: Akela1101
 *
 * Created on 10 Январь 2011 г., 10:09
 */

#ifndef _GAME_H
#define	_GAME_H

#include "StrategixSingleton.h"

#include <vector>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;

	class Map;
	class Player;
	
	class Game : public StrategixSingleton<Game>
	{
	public:
		//Map map;
		sh_p<Map> map;
		vector<sh_p<Player> > players;

	public:
		void Start(string mapName, vector<sh_p<Player> > players);
		void Tick(const float seconds);

		inline Map &GetMap() { return *map; }
	};
}

#endif	/* _GAME_H */

