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
#include "StrategixError.h"

#include "Enti.h"


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

Enti::~Enti()
{
}

void Enti::Tick(const float seconds)
{
	for( list<Feature*>::iterator itFeature = tickFeatures.begin();
			itFeature != tickFeatures.end(); ++itFeature )
	{
		if( !(*itFeature)->Tick(seconds) )
		{
			tickFeatures.erase(itFeature++); // removing from Tick queue
		}
	}
	unit->OnTick(seconds);
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
	else
	{
		// @#~ !!!!!!!!!!!
		//STRATEGIX_ERROR(string("Unable to create feature named: ") + name);
		return sh_p<Feature>();
	}
}

bool Enti::Move(const RealCoord newCoord)
{
	FeatureMove* featureMove = dynamic_cast<FeatureMove*>(GetFeature("move"));
	if( featureMove )
	{
		featureMove->Move(newCoord);
		return true;
	}
	return false;
}

}