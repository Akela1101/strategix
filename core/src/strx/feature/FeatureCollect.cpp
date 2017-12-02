#include <strx/entity/Enti.h>
#include <strx/entity/EntiInfo.h>
#include <strx/entity/EntiSlot.h>
#include <strx/feature/FeatureMove.h>
#include <strx/map/Map.h>
#include <strx/player/Player.h>
#include <strx/common/TechTree.h>

#include "FeatureCollect.h"


namespace strx
{

FeatureCollect::FeatureCollect(const FeatureInfo* featureInfo, Enti* enti)
		: Feature(enti), featureInfoCollect(dynamic_cast<const FeatureInfoCollect*>(featureInfo)), load(0)
		, isMovingToCollector(false) {}

bool FeatureCollect::Collect(Mine* mine)
{
	if (!mine)
		return false;
	
	// Try move and set OnComplete for this
	if (!enti->Do<FeatureMove>()->Move(mine->GetCoord(), this))
		return false;
	
	// Setting target resource
	this->mine = mine;
	
	resourceName = mine->GetResourceName();
	capacity = featureInfoCollect->capacities->at(resourceName);
	isMovingToCollector = false;
	
	return true;
}

bool FeatureCollect::Tick(float seconds)
{
	// If Enti is not full and resource still exists
	if (load < capacity && mine->GetResource())
	{
		float piece = seconds * featureInfoCollect->speed;
		if (piece > capacity - load)
		{
			piece = capacity - load; // all it can bring
		}
		load += enti->GetPlayer().GetMap().PickResource(mine, piece);
		
		enti->GetSlot().OnCollect();
	}
	else // full load or no more resources
	{
		Stop();
		MoveToCollector();
		return false;
	}
	return true;
}

void FeatureCollect::Stop()
{
	enti->GetSlot().OnCollectStop();
}

void FeatureCollect::OnComplete(bool isComplete)
{
	if (!isComplete)
		return;
	
	if (!isMovingToCollector) // neared to the resource
	{
		if (load < capacity)
		{
			enti->GetSlot().OnCollectStart();
			enti->AssignTickFeature(this);
		}
		else
		{
			MoveToCollector();
		}
	}
	else // neared to the collector, so unload
	{
		enti->GetSlot().OnBringStop();
		enti->GetPlayer().AddResource(*Kernel::MakeResource(resourceName, load));
		load = 0;
		
		// Going back to resource
		if (mine)
		{
			Collect(mine);
		}
	}
}

const Enti* FeatureCollect::FindCollector()
{
	// @#~ Check if there is path to Collector and also select nearest
	// @#~ Check out the case when there are no collectors or more than one
	
	for (auto&& enti : enti->GetPlayer().entis)
	{
		if (enti->GetInfo().kind == "building") // @#~ should be building type check
		{
			return enti.get();
		}
	}
	return nullptr;
}

void FeatureCollect::MoveToCollector()
{
	const Enti* collector = FindCollector();
	
	if (collector && enti->Do<FeatureMove>()->Move(collector->GetCoord(), this))
	{
		isMovingToCollector = true;
	}
}

}
