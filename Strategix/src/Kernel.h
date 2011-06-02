/* 
 * File:   Kernel.h
 * Author: Akela1101
 *
 * Created on 10 Январь 2011 г., 10:09
 */

#ifndef _KERNEL_H
#define	_KERNEL_H

#include <vector>

#include "Strategix_Forward.h"


namespace Strategix
{
	using namespace std;
	
	class Kernel
	{
	public:
		sh_p<MapFull> mapFull;
		vector<sh_p<Player> > players; // @#~ map better...

	public:		
		Kernel(const string &mapName);
		void AddPlayer(sh_p<Player> player);

		void Start();
		void Tick(const float seconds);

		inline MapFull &GetMap() { return *mapFull; }
	};
}

#endif	/* _KERNEL_H */

