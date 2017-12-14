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
		: Feature(entity), featureInfoCollect(dynamic_cast<const FeatureInfoCollect*>(featureInfo)), load(0)
		, isMovingToCollector(false) {}

bool FeatureCollect::Collect(MapCoord coord, const string& resourceName)
{
	// try move and set OnComplete for this
	if (!entity->Do<FeatureMove>()->Move(coord, this)) return false;
	
	// setting target resource
	this->coord = coord;
	this->resourceName = resourceName;
	capacity = featureInfoCollect->capacities->at(resourceName);
	isMovingToCollector = false;
	
	info_log << "start collect: [%s, %d] (%d, %d)"s % resourceName % capacity % coord.x % coord.y;
	return true;
}

void FeatureCollect::Tick(float seconds)
{
	// If Entity is not full and resource still exists
	Map& map = entity->GetPlayer().GetMap();
	auto mine = dynamic_cast<MapMine*>(map.GetCell(coord).object.get());
	
	if (load < capacity && mine)
	{
		float piece = seconds * featureInfoCollect->speed;
		if (piece > capacity - load)
		{
			piece = capacity - load; // all it can bring
		}
		load += map.PickResource(mine, piece);
		
		entity->GetSlot().OnCollect();
		return;
	}
	
	// full load or no more resources
	MoveToCollector();
}

void FeatureCollect::Stop()
{
	info_log << "stop collect";
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
		entity->GetSlot().OnCollectStart();
		entity->AssignTask(this);
		return;
	}
	
	MoveToCollector();
}

const Entity* FeatureCollect::FindCollector()
{
	// @#~ Check if there is path to Collector and also select nearest
	// @#~ Check out the case when there are no collectors or more than one
	
	for (auto&& entity : entity->GetPlayer().entis)
	{
		if (entity->GetInfo().kind == "building") // @#~ should be building type check
		{
			return entity.get();
		}
	}
	return nullptr;
}

void FeatureCollect::MoveToCollector()
{
	const Entity* collector = FindCollector();
	
	if (collector && entity->Do<FeatureMove>()->Move(collector->GetCoord(), this))
	{
		isMovingToCollector = true;
	}
}

}
