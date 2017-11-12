#include "Enti.h"
#include "EntiInfo.h"
#include "EntiSlot.h"
#include "MapLocal.h"
#include "Player.h"
#include "ResourceInfo.h"
#include "TechTree.h"


namespace Strategix
{

FeatureCollect::FeatureCollect(const FeatureInfo* featureInfo, Enti* enti)
		: Feature(enti), featureInfoCollect(dynamic_cast<const FeatureInfoCollect*>(featureInfo)), load(0)
		, isMovingToCollector(false) {}

bool FeatureCollect::Collect(s_p<MapResource> mapResource)
{
	if (!mapResource)
		return false;
	
	// Try move and set OnComplete for this
	if (!enti->Do<FeatureMove>()->Move(mapResource->GetCoord(), this))
		return false;
	
	// Setting target resource
	this->mapResource = mapResource;
	
	resourceName = mapResource->GetResourceInfo()->name;
	capacity = featureInfoCollect->capacities->at(resourceName);
	isMovingToCollector = false;
	
	return true;
}

bool FeatureCollect::Tick(float seconds)
{
	// If Enti is not full and resource still exists
	if (load < capacity && mapResource->GetResource())
	{
		float piece = seconds * featureInfoCollect->speed;
		if (piece > capacity - load)
		{
			piece = capacity - load; // all it can bring
		}
		load += enti->GetPlayer().GetMapLocal().PickResource(mapResource, piece);
		
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
	if (mapResource && mapResource->GetResource() == 0)
	{
		mapResource.reset();
	}
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
		if (mapResource)
		{
			Collect(mapResource);
		}
	}
}

const Enti* FeatureCollect::FindCollector()
{
	// @#~ too simple
	// @#~ Check if there is path to Collector and also select nearest
	// @#~ Check out the case when there are no collectors or more than one !!!
	
	const string collectorName = enti->GetPlayer().techTree->mainBuildingName;
	for (s_p<const Enti> enti : enti->GetPlayer().entis)
	{
		if (enti->GetInfo().name == collectorName)
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
