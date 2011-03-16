/*
 * File:   MovingUnit.cpp
 * Author: Akela1101
 *
 * Created on 15 Апрель 2010 г., 13:57
 */

#include "MyAppCommon.h"
#include "LabelUnit.h"

#include "OgreSceneManager.h"

#include "EntiInfo.h"
#include "Map.h"
#include "Kernel.h"
#include "Exception.h"

#include <vector>
#include <sstream>

#include "Nya.hpp"
#include "MovingUnit.h"

namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;
	using namespace std;

	// Draw debug info
		typedef sh_p<LabelUnit> ShpLabelUnit;
		typedef std::vector<ShpLabelUnit> LabelVector;
		static LabelVector labelVector;
		//

MovingUnit::MovingUnit(const String &name, const MapCoord &mapCoord)
	:
	EntityUnit(name, mapCoord ),
	distance(0.0f),
	moveSpeed(30.0f)
{
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	const EntiInfo *ei;// = player->techTree.techMap[name].get();
	
	string meshFile = ei->file;
	entity = sceneManager->createEntity(meshFile);
	entity->setUserAny(Any(this)); // Link from Entity to itself
	entity->setQueryFlags(MOV_MASK);

	node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(entity);
	float scale = ei->scale;
	node->setScale(scale, scale, scale);
	node->setPosition(GetDiscretePos(mapCoord));
	destination = node->getPosition();

	// @#~ Maybe better to = 0 and so on
	moveList = new std::deque< MapCoord>();


//	// Title
//	Camera* camera = sceneManager->getCamera("Camera");
//	if( !camera )
//		STRATEGIX_ERROR("No camera named Camera");
//
//	objectTitle = new ObjectTitle("Title", entity, camera, "This is Robot", "StarWars");
}

MovingUnit::~MovingUnit()
{
	// delete moveList ?
	//delete objectTitle;
	node->detachObject(entity);
	sceneManager->destroyEntity(entity);
	sceneManager->destroySceneNode(node);
}

void MovingUnit::Tick(Real time)
{
	// Updating Titles above Entity
	// objectTitle->update();
	foreach( ShpLabelUnit labelUnit, labelVector )
	{
		labelUnit->Update();
	}

	// Moving
	if( distance <= 0.0f )
	{
		if( moveList->empty() ) // Standing
		{
			node->setPosition(destination);

			try
			{
				if( animationState != entity->getAnimationState("Idle") )
				{
					animationState = entity->getAnimationState("Idle");
					animationState->setLoop(true);
					animationState->setEnabled(true);
				}
			}
			catch( ItemIdentityException )
			{
				cout << endl << "No default Idle action" << endl;
			}
		}
		else // Moving next position
		{
			try
			{
				if( animationState != entity->getAnimationState("Move") )
				{
					animationState = entity->getAnimationState("Move");
					animationState->setLoop(true);
					animationState->setEnabled(true);
				}
			}
			catch( ItemIdentityException )
			{
				cout << endl << "No default Move action" << endl;
			}

			mapCoord = moveList->front(); // Setting current position
			destination = GetDiscretePos(mapCoord); // Setting 3D coordinates
			moveList->pop_front();

			direction = destination - node->getPosition();
			distance = direction.normalise();

			Vector3 src = node->getOrientation() * Vector3::UNIT_X;
			if( (1.0f + src.dotProduct(direction)) < 0.01f )
			{
				node->yaw(Degree(180));
			}
			else
			{
				Quaternion quat = src.getRotationTo(Vector3(direction.x, 0, direction.z));
				node->rotate(quat);
			}
		}

		// animationState->addTime(time);
	}
	else // Moving if( distance > 0.0f )
	{
		Real moving = moveSpeed * time;
		distance -= moving;

		// @#~ Might be troubles, if distance become much less than 0!!!!

		node->translate(Vector3(direction.x, 0, direction.z) * moving);

		animationState->addTime(moving / 10);
	}
}

void MovingUnit::AddWayTo(Vector3 &pos)
{
	delete moveList;
	// !!!!!!!!!!!!!!!!
	// moveList = kernel->GetMap().BuildWay(mapCoord, GetMapCoord(pos));
}

void MovingUnit::AddWayTo_Debug(Vector3 &pos)
{	
	static MapCoord oldMapCoord = MapCoord(-1, -1);
	MapCoord newMapCoord = GetMapCoord(pos);

	typedef std::deque< MapCoord> MapCoordDeque;
	static MapCoordDeque *saved_moveList;

	// First time mouse click => Draw path
	if( oldMapCoord != newMapCoord )
	{
		oldMapCoord = newMapCoord;

		typedef std::list< Map::Cell*> CellList;
		CellList *p_closed = 0;

		// !!!!!!!!!!!!!!!
		// saved_moveList =  kernel->GetMap().BuildWay_Debug(mapCoord, newMapCoord, p_closed);

		//
		labelVector.clear();
		labelVector.reserve(p_closed->size());

		for( CellList::iterator at = p_closed->begin(); at != p_closed->end(); ++at)
		{
			std::stringstream title;
			title << "\n" << (*at)->G << " + " << (*at)->H << "\n = " << (*at)->F ;
			ShpLabelUnit labelUnit(new LabelUnit((*at)->mc, title.str().c_str()));

			if( saved_moveList->end() != find(saved_moveList->begin(), saved_moveList->end(), (*at)->mc) )
				labelUnit->SetColor(ColourValue(1.0, 1.0, 1.0, 1.0));
			else
				labelUnit->SetColor(ColourValue(5.0, 0.0, 0.8, 1.0));

			labelVector.push_back(labelUnit);
		}

		delete p_closed;
	}	
	else // Second time mouse click => Go
	{
		if( moveList != saved_moveList )
			delete moveList;
		moveList = saved_moveList;
	}
}

inline  MapCoord MovingUnit::GetMapCoord(const Vector3 &pos)
{
	return  MapCoord(pos.x / tile_length, pos.z / tile_length);
}

inline Vector3 MovingUnit::GetDiscretePos(const  MapCoord &mapCoord)
{
	return Vector3((mapCoord.x + 0.5f) * tile_length, 0, (mapCoord.y + 0.5f) * tile_length);
}

inline Vector3 MovingUnit::GetDiscretePos(const Vector3 &pos)
{
	return GetDiscretePos(GetMapCoord(pos));
}

}

