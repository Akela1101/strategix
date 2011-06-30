/* 
 * File:   Kernel.cpp
 * Author: Akela1101
 * 
 * Created on 10 Январь 2011 г., 10:09
 */

#include "Enti.h"
#include "KernelBase.h"
#include "MapFull.h"
#include "MapLocal.h"
#include "MapResource.h"
#include "Player.h"
#include "TechTree.h"

#include "Kernel.h"


namespace Strategix
{

Kernel::Kernel(const string &mapName)
{
	mapFull.reset(new MapFull(mapName));
}

void Kernel::AddPlayer(sh_p<Player> player)
{
	player->mapLocal.reset(new MapLocal(player.get(), mapFull.get()));
	players.push_back(player);
}

void Kernel::Start()
{
	// @#~ Check for kernel consistence, run initial functions

	// Players' initialization
	foreach( sh_p<Player > &player, players )
	{
		player->Start();
	}

	// @#~
	players[0]->AddEnti(sh_p<Enti>(new Enti(&*players[0]->techTree->Node("Spher_Worker"), MapCoord(4, 16))));
	players[0]->AddEnti(sh_p<Enti>(new Enti(&*players[0]->techTree->Node("Spher_Worker"), MapCoord(6, 17))));
	players[0]->AddEnti(sh_p<Enti>(new Enti(&*players[0]->techTree->Node("Spher_Worker"), MapCoord(6, 16))));

	// @#~
	players[0]->AddResource(KernelBase::GS().MakeResource("gold", 0)); // badly refreshing
}

void Kernel::Tick(const float seconds)
{
	foreach( sh_p<Player> player, players )
	{
		player->Tick(seconds);
	}
}

}