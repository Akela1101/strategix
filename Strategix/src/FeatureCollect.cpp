/* 
 * File:   FeatureCollect.cpp
 * Author: Akela1101
 * 
 * Created on 18 Май 2011 г., 14:48
 */


#include "FeatureInfo.h"
#include "Enti.h"
#include "Unit.h"
#include "Player.h"
#include "MapResource.h"
#include "MapLocal.h"

#include "FeatureCollect.h"


namespace Strategix
{

FeatureCollect::FeatureCollect(const FeatureInfo *featureInfo, Enti *enti)
	:
	Feature(enti),
	featureInfoCollect(static_cast<const FeatureInfoCollect*>(featureInfo)),
	capacity(featureInfoCollect->capacity),
	load(0),
	collector(0)
{
}

bool FeatureCollect::Collect(sh_p<MapResource> mapResource)
{
	if( load >= capacity ) // @#~ Add other conditions
		return false;

	// Try move and set callback on this
	if( !enti->Move(mapResource->mapCoord, this) )
		return false;

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

		// Кусок влезает
		if( load + piece < capacity )
		{
			// Ресурс закончился
			if( piece == shMapResource->amount )
			{
				shMapResource->amount = 0;
				// remove resource from Map
				MapCoord mapCoord = shMapResource->mapCoord;
				enti->player->mapLocal->GetCell(mapCoord).mapResource.reset();
			}
			// Ресурс ещё есть
			else
			{
				shMapResource->amount -= piece;
			}			
			load += piece;
		}
		// Кусок не влезает
		else
		{
			// Суём то, что влезает
			shMapResource->amount -= capacity - load;
			load = capacity;
		}
		enti->unit->OnCollect();
	}
	else
	{
		enti->unit->OnCollectStop();

		// Going back to base(or collector)
		if( !collector || !enti->Move(collector->coord, this) )
		{
			collector = enti->FindCollector();
			enti->Move(collector->coord, this); // @#~ go till building radius !!!
		}
		return false;
	}
	return true;
}

void FeatureCollect::OnMoveStart()
{
	enti->unit->OnMoveStart();
}

void FeatureCollect::OnMove()
{
	enti->unit->OnMove();
}

void FeatureCollect::OnMoveStop()
{
	if( load == 0 )
	{
		// @#~ Check if Enti is near resourse
		enti->unit->OnMoveStop();
		enti->unit->OnCollectStart();
		enti->tickFeatures.push_back(this); // adding to Tick queue
	}
	// Near the collector, so unload
	else
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

}
