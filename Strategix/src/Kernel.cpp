/* 
 * File:   Kernel.cpp
 * Author: Akela1101
 * 
 * Created on 10 Январь 2011 г., 10:09
 */

#include "MapFull.h"
#include "MapLocal.h"
#include "Player.h"

#include "Kernel.h"

namespace Strategix
{

Kernel::Kernel(const string &mapName)
{
	mapFull.reset(new MapFull(mapName));
}

void Kernel::AddPlayer(sh_p<Player> player)
{
	player->map.reset(new MapLocal(mapFull.get()));
	players.push_back(player);
}

void Kernel::Tick(const float seconds)
{
	foreach( sh_p<Player> player, players )
	{
		player->Tick(seconds);
	}
}

}