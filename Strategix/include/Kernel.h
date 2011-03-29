/* 
 * File:   Kernel.h
 * Author: Akela1101
 *
 * Created on 10 Январь 2011 г., 10:09
 */

#ifndef _KERNEL_H
#define	_KERNEL_H

#include <vector>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;

	class MapFull;
	class Player;
	
	class Kernel
	{
	public:
		sh_p<MapFull> mapFull;
		vector<sh_p<Player> > players;

	public:		
		Kernel(const string &mapName);
		void AddPlayer(sh_p<Player> player);
		void Tick(const float seconds);

		inline MapFull &GetMap() { return *mapFull; }
	};
}

#endif	/* _KERNEL_H */

