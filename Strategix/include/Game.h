/* 
 * File:   Game.h
 * Author: Akela1101
 *
 * Created on 10 Январь 2011 г., 10:09
 */

#ifndef _GAME_H
#define	_GAME_H

#include "Nya.hpp"
#include "Log.h"
#include "Map.h"
#include "Player.h"
#include "GameStructs.h"

#include <vector>


namespace Strategix
{
	using namespace std;

	class Game : public StrategixSingleton<Game>
	{
	public:
		//Map map;
		sh_p<Map> map;
		vector<sh_p<Player> > players;

	public:
		void Start(string mapName, vector<sh_p<Player> > players);

		inline Map &GetMap() { return *map; }
	};
}

#endif	/* _GAME_H */

