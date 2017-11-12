#include "Enti.h"
#include "EntiSlot.h"
#include "FeatureInfo.h"
#include "MapLocal.h"
#include "MapsPath.h"
#include "Player.h"

#include "FeatureMove.h"


namespace Strategix
{

FeatureMove::FeatureMove(const FeatureInfo* featureInfo, Enti* enti)
		: Feature(enti)
		, featureInfoMove(dynamic_cast<const FeatureInfoMove*>(featureInfo))
		, speed(featureInfoMove->speed)
		, finish(enti->GetCoord())
		, isMoving(false)
{}

bool FeatureMove::Move(const RealCoord newCoord, ICommand* iCommand)
{
	this->iCommand = iCommand;
	distance = 0;
	mapsPath = enti->GetPlayer().GetMapLocal().FindPath(enti->GetCoord(), newCoord);
	
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
	if (distance > 0) // Moving
	{
		float moving = seconds * speed;
		distance = (distance > moving) ? (distance - moving) : 0;
		enti->GetCoord() = finish - direction * distance;
		enti->GetSlot().OnMove();
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
