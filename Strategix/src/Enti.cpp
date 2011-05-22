/* 
 * File:   Enti.cpp
 * Author: Akela1101
 * 
 * Created on 4 Февраль 2011 г., 18:41
 */

#include "Unit.h"
#include "Player.h"
#include "EntiInfo.h"
#include "FeatureMove.h"
#include "FeatureCollect.h"
#include "StrategixError.h"

#include "Enti.h"
#include "Map.h"
#include "TechTree.h"


namespace Strategix
{

Enti::Enti(const EntiInfo *entityInfo, const MapCoord &mapCoord)
	:
	entityInfo(entityInfo),
	coord(mapCoord)
{
	foreach(const EntiInfo::FeatureInfosType::value_type &pa, entityInfo->featureInfos)
	{
		features[pa.first] = CreateFeature(pa.first, pa.second.get());
	}
}

void Enti::Tick(const float seconds)
{
	for( list<Feature*>::iterator itFeature = tickFeatures.begin();
			itFeature != tickFeatures.end(); )
	{
		if( !(*itFeature)->Tick(seconds) )
		{
			tickFeatures.erase(itFeature++); // removing from Tick queue
		}
		else
		{
			++itFeature;
		}
	}
	unit->OnTick(seconds);
}

bool Enti::Move(const RealCoord newCoord, IMove *iMove)
{
	FeatureMove* featureMove = dynamic_cast<FeatureMove*>(GetFeature("move"));
	if( featureMove )
	{
		featureMove->Move(newCoord, iMove ? iMove : unit); // if Zero, send this->unit
		return true;
	}
	return false;
}

bool Enti::Collect(sh_p<MapResource> mapResource)
{
	FeatureCollect* featureCollect = dynamic_cast<FeatureCollect*>(GetFeature("collect"));
	if( featureCollect )
	{
		featureCollect->Collect(mapResource);
		return true;
	}	
	return false;
}

Enti* Enti::FindCollector()
{
	// @#~ too simple
	// @#~ Check if there is path to Collector and also select nearest
	// @#~ Check out the case when there are no collectors or more than one !!!


	const string collectorName = player->techTree->mainBuildingName;
	return player->entis.find(collectorName)->second.get();
}

Feature* Enti::GetFeature(const string &name)
{
	FeaturesType::iterator feature = features.find(name);
	if( feature != features.end() )
	{
		return feature->second.get();
	}
	cout << string("There is no feature named: ") + name << endl; // DEBUG @#~
	return 0;
}

sh_p<Feature> Enti::CreateFeature(const string &name, const FeatureInfo *featureInfo)
{
	if( name == "move" )
	{
		return sh_p<FeatureMove>(new FeatureMove(featureInfo, this));
	}
	else if( name == "collect" )
	{
		return sh_p<FeatureCollect>(new FeatureCollect(featureInfo, this));
	}
	else
	{
		// @#~ !!!!!!!!!!!
		//STRATEGIX_ERROR(string("Unable to create feature named: ") + name);
		return sh_p<Feature>();
	}
}

}