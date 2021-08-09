#include "../../strx/EntityInfo.hpp"
#include "../../strx/Map.hpp"
#include "../../strx/MapMine.hpp"
#include "../../strx/TechTree.hpp"
#include "../game/PlayerKernel.hpp"
#include "EntityKernel.hpp"
#include "FeatureMove.hpp"

#include "FeatureCollect.hpp"


namespace strx
{
static const float mineSelectionRadius = 10;

FeatureCollect::FeatureCollect(const FeatureInfo* featureInfo, EntityKernel* entity)
        : Feature(entity)
        , info(dynamic_cast<const CollectFeatureInfo*>(featureInfo))
        , load(0)
        , isMovingToCollector(false)
{}

bool FeatureCollect::Collect(MapCoord coord, const string& resourceName)
{
	// check if entity can bear this resource
	if (!nya_in(resourceName, *info->capacities)) return false;

	if (this->resourceName != resourceName)
	{
		this->resourceName = resourceName;
		this->capacity = info->capacities->at(resourceName);

		if (load != 0) load = 0;  // throw out current resource
	}
	Collect(coord);
	return true;
}

void FeatureCollect::Tick(float seconds)
{
	if (MapMine* mine = SelectMine())
	{
		ResourceUnit piece = min(ResourceUnit(seconds * info->speed), capacity - load);
		load += entity->GetPlayer().PickResource(mine, piece);

		//@#~entity->GetSlot().OnCollect();
	}
}

void FeatureCollect::Stop()
{
	//@#~entity->GetSlot().OnCollectStop();
}

void FeatureCollect::Completed(bool done)
{
	if (!done) return;  // @#~ move failed — probably it needs some wakeup timer to retry move

	if (isMovingToCollector)  // near the collector, so unload
	{
		//@#~entity->GetSlot().OnBringStop();
		entity->GetPlayer().AddResource(Resource(resourceName, load));
		load = 0;

		// Going back to resource
		Collect(coord);
		return;
	}

	if (SelectMine())  // near the mine, so try to load
	{
		//@#~entity->GetSlot().OnCollectStart();
		entity->AssignTask(this);
	}
}

void FeatureCollect::Collect(MapCoord coord)
{
	// move and wait it done
	entity->Do<FeatureMove>().Move(coord, info->radius, this);

	this->coord = coord;
	this->isMovingToCollector = false;

	//info_log << "start collect: [%s, %d] (%d, %d)"s % resourceName % capacity % coord.x % coord.y;
}

void FeatureCollect::MoveToCollector()
{
	if (EntityKernel* collector = entity->GetPlayer().FindCollector(entity->GetCoord()))
	{
		entity->Do<FeatureMove>().Move(collector->GetCoord(), info->radius, this);
		isMovingToCollector = true;
	}
}

MapMine* FeatureCollect::SelectMine()
{
	if (load < capacity)
	{
		PlayerKernel& player = entity->GetPlayer();
		auto mine = player.GetMine(coord);
		if (mine) return mine;

		if (mine = player.FindMine(entity->GetCoord(), resourceName, mineSelectionRadius))
		{
			Collect(mine->coord);  // change current mine
		}
		return nullptr;
	}
	MoveToCollector();
	return nullptr;
}

}  // namespace strx
