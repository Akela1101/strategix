#include <boost/core/demangle.hpp>
#include <strx/feature/FeatureMove.h>
#include <strx/feature/FeatureCollect.h>
#include <strx/feature/FeatureHealth.h>
#include <strx/feature/FeatureAttack.h>

#include "EntiInfo.h"
#include "EntiSlot.h"
#include "Enti.h"


namespace strx
{
Enti::Enti(const EntiInfo& entiInfo, int id, const RealCoord& coord, Player* player)
		: player(player)
		, entiInfo(entiInfo)
		, id(id)
		, coord(coord)
		, tickFeature(nullptr)
{
	for (auto&& pa : entiInfo.featureInfos)
	{
		AddFeature(pa.first, pa.second.get());
	}
}

Enti::~Enti() = default;

Feature* Enti::GetFeature(type_index type) const
{
	auto iFeature = features.find(type);
	if (iFeature == features.end())
	{
		info_log << "%s has no feature %s"s % entiInfo.name % boost::core::demangle(type.name());
		return nullptr;
	}
	return iFeature->second.get();
}

void Enti::AddFeature(const string& name, const FeatureInfo* featureInfo)
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

void Enti::SetSlot(EntiSlot* slot)
{
	this->slot = slot;
}

void Enti::Tick(float seconds)
{
	for (auto itFeature = passiveTickFeatures.begin(); itFeature != passiveTickFeatures.end();)
	{
		if (!(*itFeature)->Tick(seconds))
		{
			passiveTickFeatures.erase(itFeature++); // removing from Tick queue
		}
		else
		{
			++itFeature;
		}
	}
	
	if (tickFeature && !tickFeature->Tick(seconds))
	{
		tickFeature = nullptr;
	}
	slot->OnTick(seconds);
}

void Enti::AssignTickFeature(Feature* feature, bool isPassive)
{
	if (isPassive)
	{
		passiveTickFeatures.push_back(feature);
	}
	else
	{
		if (tickFeature) tickFeature->Stop();
		
		tickFeature = feature;
	}
}

}