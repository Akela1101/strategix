/*
 * File:   MovingManager.cpp
 * Author: Akela1101
 *
 * Created on 15 Апрель 2010 г., 13:57
 */

#include "Nya.hpp"
#include "Game.h"
#include "MovingManager.h"
#include "OgreWrapCommon.h"
#include "LabelManager.h"

#include "OgreException.h"
#include <vector>
#include <sstream>

namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;
	using namespace std;

MovingManager::MovingManager(Player *player, const String &name, const MapCoord &mapCoord)
	:
	EntityManager(player, name, mapCoord ),
	distance(0.0f),
	moveSpeed(30.0f)
{
	const EntiInfo *ei = player->techTree.techMap[name].get();
	
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
	moveList = new std::deque<Strategix::MapCoord>();


//	// Title
//	Camera* camera = sceneManager->getCamera("Camera");
//	if( !camera )
//		OGRE_EXCEPT(1, "No camera named Camera", "");
//
//	objectTitle = new ObjectTitle("Title", entity, camera, "This is Robot", "StarWars");
}

MovingManager::~MovingManager()
{
	// delete moveList ?
	//delete objectTitle;
	node->detachObject(entity);
	sceneManager->destroyEntity(entity);
	sceneManager->destroySceneNode(node);
}

bool MovingManager::frameRenderingQueued(const FrameEvent &event)
{
	MoveOnTime(event.timeSinceLastFrame);
	//objectTitle->update();
	return true;
}

void MovingManager::AddWayTo(Vector3 &pos)
{
	delete moveList;
	moveList = Strategix::Game::GS().GetMap().BuildWay(mapCoord, GetMapCoord(pos));
}

void MovingManager::AddWayTo_Debug(Vector3 &pos)
{
	using Strategix::MapCoord;
	
	static MapCoord oldMapCoord = MapCoord(-1, -1);
	MapCoord newMapCoord = GetMapCoord(pos);

	typedef std::deque<Strategix::MapCoord> MapCoordDeque;
	static MapCoordDeque *saved_moveList;

	// First time mouse click => Draw path
	if( oldMapCoord != newMapCoord )
	{
		oldMapCoord = newMapCoord;

		typedef std::list<Strategix::Map::Cell*> CellList;
		CellList *p_closed = 0;

		saved_moveList = Strategix::Game::GS().GetMap().BuildWay_Debug(mapCoord, newMapCoord, p_closed);

		//Strategix::Log::GS().Write("hahahah\n");

		// Draw debug info
		typedef sh_p<LabelManager> SHP_LabelManager;
		typedef std::vector<SHP_LabelManager> LabelVector;
		static LabelVector labelVector;
		//
		labelVector.clear();
		// Very Bad Solution of Very Simple Issue !!!!
				Root::getSingleton().renderOneFrame();

		labelVector.reserve(p_closed->size());

		for( CellList::iterator at = p_closed->begin(); at != p_closed->end(); ++at)
		{
			std::stringstream title;
			title << "\n" << (*at)->G << " + " << (*at)->H << "\n = " << (*at)->F ;
			SHP_LabelManager shp_labelManager(new LabelManager((*at)->mc, title.str().c_str()));

			if( saved_moveList->end() != find(saved_moveList->begin(), saved_moveList->end(), (*at)->mc) )
				shp_labelManager->SetColor(ColourValue(1.0, 1.0, 1.0, 1.0));
			else
				shp_labelManager->SetColor(ColourValue(5.0, 0.0, 0.8, 1.0));

			labelVector.push_back(shp_labelManager);
		}

		delete p_closed;
	}
	// Second time mouse click => Go
	else
	{
		if( moveList != saved_moveList )
			delete moveList;
		moveList = saved_moveList;
	}
}

void MovingManager::MoveOnTime(Real time)
{
	if( distance <= 0.0f )
	{
		node->setPosition(destination);

		if( moveList->empty() ) // Standing
		{
			try
			{
				animationState = entity->getAnimationState("Idle");
				animationState->setLoop(true);
				animationState->setEnabled(true);
			}
			catch( ItemIdentityException )
			{
				cout << endl << "No default Idle action" << endl;
			}			
		}
		else // Moving next position
		{			
			animationState = entity->getAnimationState("Move");
			animationState->setLoop(true);
			animationState->setEnabled(true);

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

		animationState->addTime(time); 
	}
	else // Moving if( distance > 0.0f )
	{
		Real move = moveSpeed * time;
		distance -= move;
		node->translate(Vector3(direction.x, 0, direction.z) * move);

		animationState->addTime(time * moveSpeed / 10); 
	}
}

inline Strategix::MapCoord MovingManager::GetMapCoord(const Vector3 &pos)
{
	return Strategix::MapCoord(pos.x / tile_length, pos.z / tile_length);
}

inline Vector3 MovingManager::GetDiscretePos(const Strategix::MapCoord &mapCoord)
{
	return Vector3((mapCoord.x + 0.5f) * tile_length, 0, (mapCoord.y + 0.5f) * tile_length);
}

inline Vector3 MovingManager::GetDiscretePos(const Vector3 &pos)
{
	return GetDiscretePos(GetMapCoord(pos));
}

}

