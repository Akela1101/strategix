/* 
 * File:   FeatureCollect.cpp
 * Author: Akela1101
 * 
 * Created on 18 Май 2011 г., 14:48
 */

#include "Enti.h"
#include "Unit.h"
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
	capacity(featureInfoCollect->capacity),
	load(0),
	collector(0),
	isMovingToCollector(false)
{
}

bool FeatureCollect::Collect(sh_p<MapResource> mapResource)
{
	// Try move and set callback on this
	if( !enti->Do<FeatureMove>()->Move(mapResource->mapCoord, this) )
		return false;

	isMovingToCollector = false;

	// Setting target resource
	this->mapResource = mapResource;
	return true;
}

bool FeatureCollect::Tick(const float seconds)
{
	// If Enti is not full and resource still exists
	sh_p<MapResource> shMapResource; // Shared
	if( load < capacity && ( shMapResource = mapResource.lock() ) )
	{
		float piece = seconds * featureInfoCollect->speed;
		if( piece > shMapResource->amount )
		{
			piece = shMapResource->amount;
		}

		// piece fits
		if( load + piece < capacity )
		{
			// resource is over
			if( piece == shMapResource->amount )
			{
				shMapResource->amount = 0;
				// remove resource from Map
				MapCoord mapCoord = shMapResource->mapCoord;
				enti->player->mapLocal->GetCell(mapCoord).mapResource.reset();
			}			
			else // resource remained
			{
				shMapResource->amount -= piece;
			}			
			load += piece;
		}		
		else // piece does not fit
		{
			// , so load all we can
			shMapResource->amount -= capacity - load;
			load = capacity;
		}
		enti->unit->OnCollect();
	}
	else // full load or no more resources
	{
		Stop();
		MoveToCollector();
		return false;
	}
	return true;
}

// Moving Complete
void FeatureCollect::OnComplete(bool isComplete)
{
	if( !isComplete )
		return;
	
	if( !isMovingToCollector ) // moving to resource complete
	{
		if( load < capacity )
		{
			enti->unit->OnCollectStart();
			enti->AssignTickFeature(this);
		}
		else
		{
			MoveToCollector();
		}
	}	
	else // near the collector, so unload
	{
		enti->unit->OnBringStop();
		enti->player->AddResources(Resources(0, load));
		load = 0;

		// Going back to resource
		if( !mapResource.expired() )
		{
			Collect(sh_p<MapResource>(mapResource));
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
	if( !collector )
	{
		collector = FindCollector(); // @#~ check if 0.
	}
	if( enti->Do<FeatureMove>()->Move(collector->coord, this) )
	{
		isMovingToCollector = true;
	}
}

void FeatureCollect::Stop()
{
	enti->unit->OnCollectStop();
}

}
