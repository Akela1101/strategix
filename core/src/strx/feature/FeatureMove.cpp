#include <strx/entity/Enti.h>
#include <strx/entity/EntiSlot.h>
#include <strx/feature/FeatureInfo.h>
#include <strx/map/Map.h>
#include <strx/map/MapsPath.h>
#include <strx/player/Player.h>

#include "FeatureMove.h"


namespace strx
{

FeatureMove::FeatureMove(const FeatureInfo* featureInfo, Enti* enti)
		: Feature(enti)
		, featureInfoMove(dynamic_cast<const FeatureInfoMove*>(featureInfo))
		, speed(featureInfoMove->speed)
		, finish(enti->GetCoord())
		, isMoving(false)
{}

FeatureMove::~FeatureMove() = default;

bool FeatureMove::Move(MapCoord coord, ICommand* iCommand)
{
	this->iCommand = iCommand;
	distance = 0;
	mapsPath = enti->GetPlayer().GetMap().FindPath(enti->GetCoord(), coord);
	
	if (!mapsPath)
		return false;
	
	if (!isMoving)
	{
		isMoving = true;
		enti->GetSlot().OnMoveStart();
		enti->AssignTickFeature(this); // adding to Tick queue
	}
	
	return true;
}

bool FeatureMove::Tick(float seconds)
{
	info_raw << "Move";
	if (distance > 0) // Moving
	{
		float moving = seconds * speed;
		distance = (distance > moving) ? (distance - moving) : 0;
		auto coord = finish - direction * distance;
		enti->GetCoord() = coord;
		enti->GetSlot().OnMove(coord);
	}
	else
	{
		if (mapsPath->IsEmpty()) // Stopping
		{
			Stop();
			if (iCommand)
				iCommand->OnComplete(true);
			
			return false;
		}
		else // Selecting next point
		{
			finish = mapsPath->PickFront();
			const RealCoord delta = finish - enti->GetCoord();
			direction = delta.Norm();
			distance = delta.Len();
		}
	}
	return true;
}

void FeatureMove::Stop()
{
	if (isMoving)
	{
		isMoving = false;
		enti->GetSlot().OnMoveStop();
	}
}

}
