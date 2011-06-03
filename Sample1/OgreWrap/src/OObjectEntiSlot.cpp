/* 
 * File:   OObjectEntiSlot.cpp
 * Author: Akela1101
 * 
 * Created on 18 Март 2011 г., 15:58
 */

#include "MyAppCommon.h"
#include "OObjectLabel.h"
#include "EntiInfoMesh.h"

#include <Strategix.h>
#include <vector>
#include <sstream>

#include "OObjectEntiSlot.h"


namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;
	using namespace std;

	// Draw debug info		
		typedef std::vector<sh_p<OObjectLabel> > LabelVector;
		static LabelVector labelVector;
		//

OObjectEntiSlot::OObjectEntiSlot(Enti *enti)
	:
	EntiSlot(enti),
	OObjectTitled(dynamic_cast<const EntiInfoMesh*>(enti->entityInfo)->meshName),
	animationState(0)
{
	entity->setUserAny(Any(this)); // Link from Entity
	entity->setQueryFlags(ENTI_MASK); // Mask for mouse selection
	
	const float scale = dynamic_cast<const EntiInfoMesh*>(enti->entityInfo)->meshScale;
	node->setScale(scale, scale, scale);
	node->setPosition(enti->coord.x, 0, enti->coord.y);

	OnMoveStop();
	OnHpChange();
}

void OObjectEntiSlot::OnTick(const float seconds)
{
	if( animationState )
	{
		animationState->addTime(seconds);
	}
	objectTitle->update();
/*
	foreach( sh_p<OObjectLabel> labelEntiSlot, labelVector )
	{
		labelEntiSlot->Update();
	}
*/
}

void OObjectEntiSlot::OnMoveStart()
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

void OObjectEntiSlot::OnMove()
{
	const RealCoord &newCoord = enti->coord;
	const Vector3 newPosition = Vector3(newCoord.x, 0, newCoord.y);
	const Vector3 direction = newPosition - node->getPosition();

	// Rotate
	Radian rad = (node->getOrientation()*Vector3::UNIT_X).angleBetween(direction);
	node->yaw(rad);
/*
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
*/
	// Move
	node->setPosition(newPosition);
}

void OObjectEntiSlot::OnMoveStop()
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

void OObjectEntiSlot::OnHpChange()
{
	HpType hp = enti->Do<FeatureHealth>()->GetHp();
	std::stringstream ss;
	ss << "HP=" << hp;
	objectTitle->setTitle(ss.str());
}

}
