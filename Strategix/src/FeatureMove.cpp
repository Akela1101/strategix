/* 
 * File:   FeatureMove.cpp
 * Author: Akela1101
 * 
 * Created on 23 Март 2011 г., 16:48
 */

#include "Unit.h"
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
	featureInfoMove(static_cast<const FeatureInfoMove*>(featureInfo)),
	vFeatureInfoMove(sh_p<FeatureInfoMove>(new FeatureInfoMove(*featureInfoMove))),	
	finish(enti->coord),
	isMoving(false)
{
}

bool FeatureMove::operator() (const RealCoord newCoord)
{
	distance = 0;
	mapsPath = enti->player->map->FindPath(enti->coord, newCoord);

	if( !mapsPath.get() )
		return false;

	if( !isMoving )
	{
		isMoving = true;
		
		enti->unit->OnMoveStart();
		enti->tickFeatures.push_back(this); // adding to Tick queue
	}

	return true;
}

bool FeatureMove::Tick(const float seconds)
{
	if( distance > 0 ) //Moving
	{
		const float moving = vFeatureInfoMove->speed * seconds;
		distance = (distance > moving) ? (distance - moving) : 0;
		enti->coord = finish - direction * distance;
		enti->unit->OnMove();
	}
	else
	{
		if( mapsPath->IsEmpty() ) // Stopping
		{
			enti->unit->OnMoveStop();
			isMoving = false;
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

}
