#include "EntiInfo.h"
#include "EntiSlot.h"

#include "Enti.h"


namespace Strategix
{
#ifndef MSCC

Enti::Enti(const EntiInfo* entiInfo, const RealCoord& coord)
		: entiInfo(entiInfo), coord(coord), tickFeature(nullptr), isLastFeature(true)
{
	for (auto&& pa : entiInfo->featureInfos)
	{
		AddFeature(pa.first, pa.second.get());
	}
}

#endif

void Enti::AddFeature(const string& name, const FeatureInfo* featureInfo)
{
	if (name == "move")
	{
		features[typeid(FeatureMove).name()].reset(new FeatureMove(featureInfo, this));
	}
	else if (name == "collect")
	{
		features[typeid(FeatureCollect).name()].reset(new FeatureCollect(featureInfo, this));
	}
	else if (name == "health")
	{
		features[typeid(FeatureHealth).name()].reset(new FeatureHealth(featureInfo, this));
	}
	else if (name == "attack")
	{
		features[typeid(FeatureAttack).name()].reset(new FeatureAttack(featureInfo, this));
	}
	// else ?
}

void Enti::Tick(const float seconds)
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
	if (tickFeature)
	{
		if (!tickFeature->Tick(seconds))
		{
			if (isLastFeature)
				tickFeature = nullptr;
			else
				isLastFeature = true;
		}
	}
	entiSlot->OnTick(seconds);
}

void Enti::AssignTickFeature(Feature* feature, bool isPassive)
{
	if (isPassive)
	{
		passiveTickFeatures.push_back(feature);
	}
	else
	{
		if (tickFeature)
			tickFeature->Stop();
		
		tickFeature = feature;
		isLastFeature = false; // do not remove tickFeature
	}
}

}