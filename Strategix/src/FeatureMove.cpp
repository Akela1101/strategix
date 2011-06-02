/* 
 * File:   FeatureMove.cpp
 * Author: Akela1101
 * 
 * Created on 23 Март 2011 г., 16:48
 */

#include "EntiSlot.h"
#include "Enti.h"
#include "Player.h"
#include "MapLocal.h"
#include "MapsPath.h"
#include "FeatureInfo.h"

#include "FeatureMove.h"


namespace Strategix
{

FeatureMove::FeatureMove(const FeatureInfo *featureInfo, Enti *enti)
	:
	Feature(enti),
	featureInfoMove(dynamic_cast<const FeatureInfoMove*>(featureInfo)),
	speed(featureInfoMove->speed),
	finish(enti->coord),
	isMoving(false)
{
}

bool FeatureMove::Move(const RealCoord newCoord, ICommand *iCommand)
{
	this->iCommand = iCommand;
	distance = 0;
	mapsPath = enti->player->mapLocal->FindPath(enti->coord, newCoord);

	if( !mapsPath )
		return false;

	if( !isMoving )
	{
		isMoving = true;		
		enti->entiSlot->OnMoveStart();
		enti->AssignTickFeature(this); // adding to Tick queue
	}

	return true;
}

bool FeatureMove::Tick(const float seconds)
{
	if( distance > 0 ) // Moving
	{
		const float moving = seconds * speed;
		distance = ( distance > moving ) ? (distance - moving) : 0;
		enti->coord = finish - direction * distance;
		enti->entiSlot->OnMove();
	}
	else
	{
		if( mapsPath->IsEmpty() ) // Stopping
		{
			Stop();
			if( iCommand )
				iCommand->OnComplete(true);

			return false;
		}
		else // Selecting next point
		{
			finish = mapsPath->PickFront();
			const RealCoord delta = finish - enti->coord;
			direction = delta.Norm();
			distance = delta.Len();
		}
	}
	return true;
}

void FeatureMove::Stop()
{
	if( isMoving )
	{
		isMoving = false;
		enti->entiSlot->OnMoveStop();
	}
}

}
