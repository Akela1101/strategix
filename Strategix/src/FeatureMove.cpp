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

#include "FeatureMove.h"


namespace Strategix
{

FeatureMove::FeatureMove()
{
}

FeatureMove::~FeatureMove()
{
}

bool FeatureMove::operator() (const RealCoord newCoord)
{
	mapsPath = enti->player->map->FindPath(enti->coord, newCoord);

	if( !mapsPath.get() )
		return false;

	enti->unit->OnMoveStart();
	enti->tickFeatures.push_back(this); // adding to Tick queue

	return true;
}

void FeatureMove::Tick(const float seconds)
{
	if( distance > 0 ) //Moving
	{
		const float moving = 30 * seconds; //speed * seconds;
		distance = (distance > moving) ? (distance - moving) : 0;
		enti->unit->OnMove(finish - direction * distance);
	}
	else
	{
		if( mapsPath->IsEmpty() ) // Stopping
		{
			enti->unit->OnMoveStop();
			enti->tickFeatures.remove(this); // removing from Tick queue
		}
		else // Selecting next point
		{
			finish = mapsPath->PickFront();
			const RealCoord delta = finish - enti->coord;
			direction = delta.Norm();
			distance = delta.Len();
		}
	}
}

}
