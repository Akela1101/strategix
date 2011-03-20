/* 
 * File:   OObjectUnit.cpp
 * Author: Akela1101
 * 
 * Created on 18 Март 2011 г., 15:58
 */

#include "MyAppCommon.h"
#include "LabelOObject.h"

#include "Enti.h"
#include "EntiInfo.h"
#include "Map.h"
#include "Kernel.h"
#include "StrategixError.h"

#include <Ogre.h>

#include <vector>
#include <sstream>

#include "Nya.hpp"
#include "OObjectUnit.h"


namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;
	using namespace std;

	// Draw debug info
		typedef sh_p<LabelOObject> ShpLabelUnit;
		typedef std::vector<ShpLabelUnit> LabelVector;
		static LabelVector labelVector;
		//

OObjectUnit::OObjectUnit(Enti *enti)
	:
	Unit(enti),
	OObject(enti->ei->file),
	distance(0.0f)
{
	entity->setUserAny(Any(this)); // Link from Entity to itself
	entity->setQueryFlags(MOV_MASK);
	
	const float scale = enti->ei->scale;
	node->setScale(scale, scale, scale);
	node->setPosition(GetDiscretePos(enti->mapCoord));
	destination = node->getPosition();
}

OObjectUnit::~OObjectUnit()
{	
}

void OObjectUnit::OnTick(float time)
{
//	foreach( ShpLabelUnit labelUnit, labelVector )
//	{
//		labelUnit->Update();
//	}
//
//	// Moving
//	if( distance <= 0.0f )
//	{
//		if( moveList->empty() ) // Standing
//		{
//			node->setPosition(destination);
//
//			try
//			{
//				if( animationState != entity->getAnimationState("Idle") )
//				{
//					animationState = entity->getAnimationState("Idle");
//					animationState->setLoop(true);
//					animationState->setEnabled(true);
//				}
//			}
//			catch( ItemIdentityException )
//			{
//				cout << endl << "No default Idle action" << endl;
//			}
//		}
//		else // Moving next position
//		{
//			try
//			{
//				if( animationState != entity->getAnimationState("Move") )
//				{
//					animationState = entity->getAnimationState("Move");
//					animationState->setLoop(true);
//					animationState->setEnabled(true);
//				}
//			}
//			catch( ItemIdentityException )
//			{
//				cout << endl << "No default Move action" << endl;
//			}
//
//			mapCoord = moveList->front(); // Setting current position
//			destination = GetDiscretePos(mapCoord); // Setting 3D coordinates
//			moveList->pop_front();
//
//			direction = destination - node->getPosition();
//			distance = direction.normalise();
//
//			Vector3 src = node->getOrientation() * Vector3::UNIT_X;
//			if( (1.0f + src.dotProduct(direction)) < 0.01f )
//			{
//				node->yaw(Degree(180));
//			}
//			else
//			{
//				Quaternion quat = src.getRotationTo(Vector3(direction.x, 0, direction.z));
//				node->rotate(quat);
//			}
//		}
//
//		// animationState->addTime(time);
//	}
//	else // Moving if( distance > 0.0f )
//	{
//		Real moving = moveSpeed * time;
//		distance -= moving;
//
//		// @#~ Might be troubles, if distance become much less than 0!!!!
//
//		node->translate(Vector3(direction.x, 0, direction.z) * moving);
//
//		animationState->addTime(moving / 10);
//	}
}

void OObjectUnit::AddWayTo(Vector3 &pos)
{
	// delete moveList;
	// !!!!!!!!!!!!!!!!
	// moveList = kernel->GetMap().BuildWay(mapCoord, GetMapCoord(pos));
}

void OObjectUnit::AddWayTo_Debug(Vector3 &pos)
{
//	static MapCoord oldMapCoord = MapCoord(-1, -1);
//	MapCoord newMapCoord = GetMapCoord(pos);
//
//	typedef std::deque< MapCoord> MapCoordDeque;
//	static MapCoordDeque *saved_moveList;
//
//	// First time mouse click => Draw path
//	if( oldMapCoord != newMapCoord )
//	{
//		oldMapCoord = newMapCoord;
//
//		typedef std::list< Map::Cell*> CellList;
//		CellList *p_closed = 0;
//
//		// !!!!!!!!!!!!!!!
//		// saved_moveList =  kernel->GetMap().BuildWay_Debug(mapCoord, newMapCoord, p_closed);
//
//		//
//		labelVector.clear();
//		labelVector.reserve(p_closed->size());
//
//		for( CellList::iterator at = p_closed->begin(); at != p_closed->end(); ++at)
//		{
//			std::stringstream title;
//			title << "\n" << (*at)->G << " + " << (*at)->H << "\n = " << (*at)->F ;
//			ShpLabelUnit labelUnit(new LabelOObject((*at)->mc, title.str().c_str()));
//
//			if( saved_moveList->end() != find(saved_moveList->begin(), saved_moveList->end(), (*at)->mc) )
//				labelUnit->SetColor(ColourValue(1.0, 1.0, 1.0, 1.0));
//			else
//				labelUnit->SetColor(ColourValue(5.0, 0.0, 0.8, 1.0));
//
//			labelVector.push_back(labelUnit);
//		}
//
//		delete p_closed;
//	}
//	else // Second time mouse click => Go
//	{
//		if( moveList != saved_moveList )
//			delete moveList;
//		moveList = saved_moveList;
//	}
}

inline  MapCoord OObjectUnit::GetMapCoord(const Vector3 &pos)
{
	return  MapCoord(pos.x / tile_length, pos.z / tile_length);
}

inline Vector3 OObjectUnit::GetDiscretePos(const  MapCoord &mapCoord)
{
	return Vector3((mapCoord.x + 0.5f) * tile_length, 0, (mapCoord.y + 0.5f) * tile_length);
}

inline Vector3 OObjectUnit::GetDiscretePos(const Vector3 &pos)
{
	return GetDiscretePos(GetMapCoord(pos));
}

}
