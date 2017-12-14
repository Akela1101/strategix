#include <boost/core/demangle.hpp>
#include <strx/feature/FeatureMove.h>
#include <strx/feature/FeatureCollect.h>
#include <strx/feature/FeatureHealth.h>
#include <strx/feature/FeatureAttack.h>

#include "strx/common/EntityInfo.h"
#include "EntitySlot.h"
#include "Entity.h"


namespace strx
{
Entity::Entity(const EntityInfo& entiInfo, int id, const RealCoord& coord, Player* player)
		: player(player)
		, entiInfo(entiInfo)
		, id(id)
		, coord(coord)
		, task(nullptr)
{
	for (auto&& pa : entiInfo.featureInfos)
	{
		AddFeature(pa.first, pa.second.get());
	}
}

Entity::~Entity() = default;

Feature* Entity::GetFeature(type_index type) const
{
	auto iFeature = features.find(type);
	if (iFeature == features.end())
	{
		info_log << "%s has no feature %s"s % entiInfo.name % boost::core::demangle(type.name());
		return nullptr;
	}
	return iFeature->second.get();
}

void Entity::AddFeature(const string& name, const FeatureInfo* featureInfo)
{
	if (name == "move")
	{
		features[typeid(FeatureMove)].reset(new FeatureMove(featureInfo, this));
	}
	else if (name == "collect")
	{
		features[typeid(FeatureCollect)].reset(new FeatureCollect(featureInfo, this));
	}
	else if (name == "health")
	{
		features[typeid(FeatureHealth)].reset(new FeatureHealth(featureInfo, this));
	}
	else if (name == "attack")
	{
		features[typeid(FeatureAttack)].reset(new FeatureAttack(featureInfo, this));
	}
	else
	{
		error_log << "Unable to handle feature " << name;
	}
}

void Entity::SetSlot(EntitySlot* slot)
{
	this->slot = slot;
}

void Entity::Tick(float seconds)
{
	for (auto&& feature : passiveTasks)
	{
		feature->Tick(seconds);
	}
	
	if (task) task->Tick(seconds);
	
	slot->OnTick(seconds);
}

void Entity::AssignTask(Feature* feature)
{
	if (task) task->Stop();
	
	task = feature;
}

void Entity::AssignPassiveTask(Feature* feature)
{
	passiveTasks.push_back(feature);
}

}