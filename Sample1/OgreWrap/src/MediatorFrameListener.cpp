/* 
 * File:   MediatorFrameListener.cpp
 * Author: Akela1101
 * 
 * Created on 13 Январь 2011 г., 21:23
 */

#include "OObjectUnit.h"

#include "EntiInfo.h"
#include "Enti.h"
#include "Player.h"
#include "Kernel.h"
#include "MapFull.h"
#include "TechTree.h"
#include "StrategixError.h"

#include "MediatorFrameListener.h"
#include "Nya.hpp"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

MediatorFrameListener::MediatorFrameListener(sh_p<Kernel> kernel)
	:
	kernel(kernel)
{
	foreach( sh_p<Player > &player, kernel->players )
	{
		// Assigning player's callback as this
		player->mediator = this;

		// Getting Base's name.
		const EntiInfo *ei = 0;
		foreach( const TechMapType::value_type &entPair, player->techTree->techMap )
		{
			if( entPair.second->kind == "building_base" )
			{
				ei = entPair.second.get();
				break;
			}
		}
		if( !ei )
		{
			STRATEGIX_ERROR("There is no defined entity with kind=building_base");
		}

		// Getting Player's Initial Position
		const MapCoord &mapCoord = kernel->GetMap().GetInitialPostion(player->playerNumber);

		// Creating Base
		sh_p<Enti> shpe(new Enti(ei, mapCoord));
		player->AddEnti(shpe);
	}
	
	// @#~
	kernel->players[0]->AddEnti(sh_p<Enti>(new Enti(&*kernel->players[0]->techTree->techMap["Spher_Worker"], MapCoord(5, 6))));
}

MediatorFrameListener::~MediatorFrameListener()
{
}

void MediatorFrameListener::OnAddEnti(Enti *enti)
{
	sh_p<OObjectUnit> unit(new OObjectUnit(enti));
	units.push_back(unit);
}

bool MediatorFrameListener::frameRenderingQueued(const FrameEvent &event)
{
	kernel->Tick(event.timeSinceLastFrame); // Time transmitting to Strategix
	return true;
}

}