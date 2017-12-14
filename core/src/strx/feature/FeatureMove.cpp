#include <strx/entity/Entity.h>
#include <strx/entity/EntitySlot.h>
#include <strx/feature/FeatureInfo.h>
#include <strx/map/Map.h>
#include <strx/map/MapPath.h>
#include <strx/player/Player.h>

#include "FeatureMove.h"


namespace strx
{

FeatureMove::FeatureMove(const FeatureInfo* featureInfo, Entity* entity)
		: Feature(entity)
		, featureInfoMove(dynamic_cast<const FeatureInfoMove*>(featureInfo))
		, isMoving(false)
		, speed(featureInfoMove->speed)
		, distance(0)
		, next(entity->GetCoord())
{}

FeatureMove::~FeatureMove() = default;

bool FeatureMove::Move(MapCoord coord, ICommand* iCommand)
{
	this->iCommand = iCommand;
	distance = 0;
	mapsPath = entity->GetPlayer().GetMap().FindPath(entity->GetCoord(), coord);
	
	if (mapsPath->IsEmpty()) return false;
	
	entity->GetSlot().OnMoveStart();
	entity->AssignTask(this);
	return true;
}

void FeatureMove::Tick(float seconds)
{
	if (distance == 0)
	{
		if (mapsPath->IsEmpty()) // Stopping
		{
			entity->AssignTask(nullptr);
			if (iCommand) iCommand->OnComplete(true);
			
			return;
		}
		
		// Selecting next point
		auto current = entity->GetCoord();
		next = mapsPath->TakeNext();
		RealCoord delta = (RealCoord)next - current;
		direction = delta.Norm();
		distance = delta.Len();
		
		auto map = entity->GetPlayer().GetMap();
		terrainQuality = 0.5 * (map.GetCell(current).terrain->quality + map.GetCell(next).terrain->quality);
	}
	
	// Moving
	float step = seconds * speed * terrainQuality;
	distance = (distance > step) ? (distance - step) : 0;
	
	RealCoord coord = next - direction * distance;
	entity->GetCoord() = coord;
	entity->GetSlot().OnMove(coord);
}

void FeatureMove::Stop()
{
	entity->GetSlot().OnMoveStop();
}

}
