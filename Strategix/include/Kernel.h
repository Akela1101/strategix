/* 
 * File:   Kernel.h
 * Author: Akela1101
 *
 * Created on 10 Январь 2011 г., 10:09
 */

#ifndef _GAME_H
#define	_GAME_H

#include <vector>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;

	class Map;
	class Player;
	
	class Kernel
	{
	public:
		sh_p<Map> fullMap;
		vector<sh_p<Player> > players;

	public:
		Kernel() {} /////// Delete it
		Kernel(const string mapName);
		void AddPlayer(sh_p<Player> player);
		void Tick(const float seconds);

		inline Map &GetMap() { return *fullMap; }
	};
}

#endif	/* _GAME_H */

