/* 
 * File:   Kernel.h
 * Author: Akela1101
 *
 * Created on 13 Февраль 2010 г., 23:19
 */

#ifndef _KERNEL_H
#define	_KERNEL_H

#include "StraxLog.h"

#include "Map.h"
#include "Player.h"
#include "TechTree.h"
#include "GameStructs.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "boost/smart_ptr.hpp"


namespace Strategix
{
	using namespace boost;

	class Kernel
	{
	private:
		Map *shared_map;
		vector<Player> players;
		map<string, shared_ptr<TechTree> > techTrees;

	public:
		Kernel();		
		virtual ~Kernel();

		// Get initial params, and prepare to start game.
		void InitGame(string mapName, vector<PlayerInitial> playerInitials);

	private:
		Kernel(const Kernel& orig);
		Kernel &operator=(const Kernel &);
	};
}

#endif	/* _KERNEL_H */

