/* 
 * File:   FeatureCollect.cpp
 * Author: Akela1101
 * 
 * Created on 18 Май 2011 г., 14:48
 */

#include "KernelBase.h"
#include "Enti.h"
#include "EntiSlot.h"
#include "Player.h"
#include "TechTree.h"
#include "MapResource.h"
#include "MapLocal.h"
#include "FeatureInfo.h"
#include "FeatureMove.h"

#include "FeatureCollect.h"


namespace Strategix
{

FeatureCollect::FeatureCollect(const FeatureInfo *featureInfo, Enti *enti)
	:
	Feature(enti),
	featureInfoCollect(dynamic_cast<const FeatureInfoCollect*>(featureInfo)),	
	isMovingToCollector(false)
{}

bool FeatureCollect::Collect(sh_p<MapResource> mapResource)
{
	if( !mapResource )
		return false;
	
	// Try move and set OnComplete for this
	if( !enti->Do<FeatureMove>()->Move(mapResource->mapCoord, this) )
		return false;

	// Setting target resource
	this->mapResource = mapResource;
	
	resourceName = mapResource->GetResourceInfo()->name;
	capacity = featureInfoCollect->capacities->at(resourceName);
	load = 0;
	isMovingToCollector = false;

	return true;
}

bool FeatureCollect::Tick(const float seconds)
{
	// If Enti is not full and resource still exists
	if( load < capacity && mapResource->GetResource() )
	{
		float piece = seconds * featureInfoCollect->speed;
		if( piece > capacity - load )
		{
			piece = capacity - load; // all it can bring
		}
		load += enti->player->mapLocal->PickResource(mapResource, piece);

		enti->entiSlot->OnCollect();
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
	enti->entiSlot->OnCollectStop();
	if( mapResource && mapResource->GetResource() == 0 )
	{
		mapResource.reset();
	}
}

void FeatureCollect::OnComplete(bool isComplete)
{
	if( !isComplete )
		return;
	
	if( !isMovingToCollector ) // neared to the resource
	{
		if( load < capacity )
		{
			enti->entiSlot->OnCollectStart();
			enti->AssignTickFeature(this);
		}
		else
		{
			MoveToCollector();
		}
	}	
	else // neared to the collector, so unload
	{
		enti->entiSlot->OnBringStop();
		enti->player->AddResource(KernelBase::GS().MakeResource(resourceName, load));
		load = 0;

		// Going back to resource
		if( mapResource )
		{
			Collect(mapResource);
		}
	}
}

Enti* FeatureCollect::FindCollector()
{
	// @#~ too simple
	// @#~ Check if there is path to Collector and also select nearest
	// @#~ Check out the case when there are no collectors or more than one !!!

	const string collectorName = enti->player->techTree->mainBuildingName;
	return enti->player->entis.find(collectorName)->second.get();
}

void FeatureCollect::MoveToCollector()
{
	Enti *collector = FindCollector(); // @#~ check if 0.

	if( enti->Do<FeatureMove>()->Move(collector->coord, this) )
	{
		isMovingToCollector = true;
	}
}

}
