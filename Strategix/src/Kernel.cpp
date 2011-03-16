/* 
 * File:   Kernel.cpp
 * Author: Akela1101
 * 
 * Created on 10 Январь 2011 г., 10:09
 */

#include "Map.h"
#include "Player.h"

#include "Kernel.h"

using namespace Strategix;


Kernel::Kernel(const string mapName)
{
	fullMap.reset(new Map(mapName));
}

void Kernel::AddPlayer(sh_p<Player> player)
{
	players.push_back(player);
}

void Kernel::Tick(const float seconds)
{
	foreach( sh_p<Player> player, players )
	{
		player->Tick(seconds);
	}
}