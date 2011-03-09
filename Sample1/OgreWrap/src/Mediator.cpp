/* 
 * File:   Mediator.cpp
 * Author: Akela1101
 * 
 * Created on 13 Январь 2011 г., 21:23
 */

#include "MovingManager.h"

#include "EntiInfo.h"
#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "TechTree.h"
#include "Exception.h"

#include "Mediator.h"
#include "Nya.hpp"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

Mediator::Mediator()
{
	foreach( sh_p<Player> &p, Game::GS().players )
	{
		// Getting Base's name.
		const string *baseName = 0;
		foreach( const TechMapType::value_type &entPair, p->techTree->techMap )
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
		MapCoord &mapCoord = Game::GS().GetMap().initialPositions[p->playerNumber];

		// Creating Base
		sh_p<MovingManager> base(new MovingManager(*baseName, mapCoord));
		AddEntityManager(base);
	}
}

Mediator::~Mediator()
{
}

bool Mediator::frameRenderingQueued(const FrameEvent &event)
{
	game->Tick(event.timeSinceLastFrame); // Time transmitting to Strategix
}

void Mediator::AddEntityManager(sh_p<EntityManager> entityManager)
{
	entityManagers.push_back(entityManager);
}

}