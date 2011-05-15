/* 
 * File:   MediatorFrameListener.cpp
 * Author: Akela1101
 * 
 * Created on 13 Январь 2011 г., 21:23
 */

#include <OgreEntity.h>
#include <OgreNode.h>

#include "OObjectUnit.h"
#include "OObjectResource.h"

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
	MapFull &mapFull = kernel->GetMap();

	// Base Buildings
	foreach( sh_p<Player > &player, kernel->players )
	{
		// Assigning player's callback as this
		player->mediator = this;

		// Getting Base Info
		const string baseName = player->techTree->mainBuildingName;
		sh_p<const EntiInfo> entityInfo = player->techTree->Node(baseName);
		
		// Getting Player's Initial Position
		const MapCoord &mapCoord = mapFull.GetInitialPostion(player->playerNumber);

		// Creating Enti
		player->AddEnti(sh_p<Enti>(new Enti(entityInfo.get(), mapCoord)));
	}

	// Resources
	for( int i = 0; i < mapFull.GetWidth(); ++i )
	{
		for( int j = 0; j < mapFull.GetLength(); ++j )
		{
			if( mapFull(i, j).resource )
			{
				sh_p<OObjectResource> res(new OObjectResource("GoldenBrick.mesh", MapCoord(i, j)));
				resources.push_back(res);
			}
		}
	}

	// @#~
	kernel->players[0]->AddEnti(sh_p<Enti>(new Enti(&*kernel->players[0]->techTree->Node("Spher_Worker"), MapCoord(5, 6))));
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