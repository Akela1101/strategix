/* 
 * File:   Mediator.cpp
 * Author: Akela1101
 * 
 * Created on 13 Январь 2011 г., 21:23
 */

#include "MovingUnit.h"

#include "EntiInfo.h"
#include "Player.h"
#include "Kernel.h"
#include "Map.h"
#include "TechTree.h"
#include "Exception.h"

#include "Mediator.h"
#include "Nya.hpp"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

Mediator::Mediator(sh_p<Kernel> kernel)
	:
	kernel(kernel)
{
	foreach( sh_p<Player> &player, kernel->players )
	{
		// Getting Base's name.
		const string *baseName = 0;
		foreach( const TechMapType::value_type &entPair, player->techTree->techMap )
		{
			if( entPair.second->kind == "building_base" )
			{
				baseName = &entPair.second->name;
				break;
			}
		}
		if( !baseName )
		{
			STRATEGIX_ERROR("There is no defined entity with kind=building_base");
		}

		// Getting Initial Position
		MapCoord &mapCoord = kernel->GetMap().initialPositions[player->playerNumber];

		// Creating Base
		sh_p<MovingUnit> base(new MovingUnit(*baseName, mapCoord));
		AddEntityUnit(base);
	}
}

Mediator::~Mediator()
{
}

bool Mediator::frameRenderingQueued(const FrameEvent &event)
{
	kernel->Tick(event.timeSinceLastFrame); // Time transmitting to Strategix
}

void Mediator::AddEntityUnit(sh_p<EntityUnit> entityUnit)
{
	entityUnits.push_back(entityUnit);
}

}