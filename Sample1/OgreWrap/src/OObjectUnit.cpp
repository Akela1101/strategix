/* 
 * File:   OObjectUnit.cpp
 * Author: Akela1101
 * 
 * Created on 18 Март 2011 г., 15:58
 */

#include "MyAppCommon.h"
#include "OObjectLabel.h"

#include "Enti.h"
#include "EntiInfoMesh.h"
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
		typedef std::vector<sh_p<OObjectLabel> > LabelVector;
		static LabelVector labelVector;
		//

OObjectUnit::OObjectUnit(Enti *enti)
	:
	Unit(enti),
	OObject(dynamic_cast<const EntiInfoMesh*>(enti->ei)->meshName),
	animationState(0)
{
	// Check all animations for corresponding mesh

	//
	entity->setUserAny(Any(this)); // Link from Entity to itself
	entity->setQueryFlags(MOV_MASK);
	
	const float scale = dynamic_cast<const EntiInfoMesh*>(enti->ei)->meshScale;
	node->setScale(scale, scale, scale);
	node->setPosition(enti->coord.x, 0, enti->coord.y);

	OnMoveStop();
}

OObjectUnit::~OObjectUnit()
{	
}

void OObjectUnit::OnTick(const float seconds)
{
	foreach( sh_p<OObjectLabel> labelUnit, labelVector )
	{
		labelUnit->objectTitle->update();
	}

	if( animationState )
	{
		animationState->addTime(seconds);
	}
}

void OObjectUnit::OnMoveStart()
{
	try
	{
		AnimationState *newAnimationState = entity->getAnimationState("Move");
		if( animationState != newAnimationState )
		{
			animationState = newAnimationState;
			animationState->setLoop(true);
			animationState->setEnabled(true);
		}
	}
	catch( ItemIdentityException )
	{
		cout << endl << "Warning: No default Move action" << endl;
	}
}

void OObjectUnit::OnMove(const RealCoord newCoord)
{
	const Vector3 newPosition = Vector3(newCoord.x, 0, newCoord.y);
	const Vector3 direction = newPosition - node->getPosition();

	// Rotate
	const Vector3 source = node->getOrientation() * Vector3::UNIT_X;
	if( (1.0 + source.dotProduct(direction)) < 0.01 )
	{
		node->yaw(Degree(180)); // Evading strange rotations
	}
	else
	{
		Quaternion quat = source.getRotationTo(direction);
		node->rotate(quat);
	}
	// Move
	node->setPosition(newPosition);
}

void OObjectUnit::OnMoveStop()
{
	try
	{
		AnimationState *newAnimationState = entity->getAnimationState("Idle");
		if( animationState != newAnimationState )
		{
			animationState = newAnimationState;
			animationState->setLoop(true);
			animationState->setEnabled(true);
		}
	}
	catch( ItemIdentityException )
	{
		cout << endl << "Warning: No default Idle action" << endl;
	}
}

//void OObjectUnit::AddWayTo_Debug(Vector3 &pos)
//{
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
//		// saved_moveList =  kernel->GetMap().FindPath_Debug(mapCoord, newMapCoord, p_closed);
//
//		//
//		labelVector.clear();
//		labelVector.reserve(p_closed->size());
//
//		for( CellList::iterator at = p_closed->begin(); at != p_closed->end(); ++at)
//		{
//			std::stringstream title;
//			title << "\n" << (*at)->G << " + " << (*at)->H << "\n = " << (*at)->F ;
//			sh_p<OObjectLabel> labelUnit(new OObjectLabel((*at)->mc, title.str().c_str()));
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
//}

}
