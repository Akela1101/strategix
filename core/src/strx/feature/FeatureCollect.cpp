#include <strx/entity/Entity.h>
#include <strx/common/EntityInfo.h>
#include <strx/entity/EntitySlot.h>
#include <strx/feature/FeatureMove.h>
#include <strx/map/Map.h>
#include <strx/map/MapMine.h>
#include <strx/player/Player.h>
#include <strx/common/TechTree.h>

#include "FeatureCollect.h"


namespace strx
{

FeatureCollect::FeatureCollect(const FeatureInfo* featureInfo, Entity* entity)
		: Feature(entity)
		, info(dynamic_cast<const FeatureInfoCollect*>(featureInfo))
		, load(0)
		, isMovingToCollector(false) {}

bool FeatureCollect::Collect(MapCoord coord, const string& resourceName)
{
	// check if entity can bear this resource
	if (!in_(resourceName, *info->capacities)) return false;
	
	// try move and set OnComplete for this
	entity->Do<FeatureMove>()->Move(coord, info->radius, this);
	
	// setting target resource
	this->coord = coord;
	this->resourceName = resourceName;
	capacity = info->capacities->at(resourceName);
	isMovingToCollector = false;
	
	//info_log << "start collect: [%s, %d] (%d, %d)"s % resourceName % capacity % coord.x % coord.y;
	return true;
}

void FeatureCollect::Tick(float seconds)
{
	// If Entity is not full and resource still exists
	Player& player = entity->GetPlayer();
	auto mine = player.GetMine(coord, resourceName);
	
	if (load < capacity && mine)
	{
		ResourceUnit piece = min(ResourceUnit(seconds * info->speed), capacity - load);
		load += player.PickResource(mine, piece);
		
		entity->GetSlot().OnCollect();
		return;
	}
	
	// full load or no more resources
	MoveToCollector();
}

void FeatureCollect::Stop()
{
	//info_log << "stop collect";
	entity->GetSlot().OnCollectStop();
}

void FeatureCollect::OnComplete(bool isComplete)
{
	if (!isComplete) return;
	
	if (isMovingToCollector) // near the collector, so unload
	{
		entity->GetSlot().OnBringStop();
		entity->GetPlayer().AddResource(Resource(resourceName, load));
		load = 0;
		
		// Going back to resource
		Collect(coord, resourceName);
		return;
	}
	
	if (load < capacity) // near the resource, so collect
	{
		if (entity->GetPlayer().GetMine(coord, resourceName))
		{
			entity->GetSlot().OnCollectStart();
			entity->AssignTask(this);
		}
		return;
	}
	
	MoveToCollector(); // load == capacity
}

void FeatureCollect::MoveToCollector()
{
	if (Entity* collector = entity->GetPlayer().FindCollector(entity->GetCoord()))
	{
		entity->Do<FeatureMove>()->Move(collector->GetCoord(), info->radius, this);
		isMovingToCollector = true;
	}
}

}
