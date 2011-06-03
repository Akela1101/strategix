/* 
 * File:   Enti.cpp
 * Author: Akela1101
 * 
 * Created on 4 Февраль 2011 г., 18:41
 */

#include "EntiInfo.h"
#include "EntiSlot.h"
#include "Map.h"
#include "Player.h"
#include "TechTree.h"

#include "Enti.h"


namespace Strategix
{

Enti::Enti(const EntiInfo *entityInfo, const RealCoord &coord)
	:
	entityInfo(entityInfo),
	coord(coord),
	tickFeature(0),
	isLastFeature(true)
{
	foreach(const EntiInfo::FeatureInfosType::value_type &pa, entityInfo->featureInfos)
	{
		AddFeature(pa.first, pa.second.get());
	}
}

void Enti::AddFeature(const string &name, const FeatureInfo *featureInfo)
{
	if( name == "move" )
	{
		features[typeid(FeatureMove).name()].reset(new FeatureMove(featureInfo, this));
	}
	else if( name == "collect" )
	{
		features[typeid(FeatureCollect).name()].reset(new FeatureCollect(featureInfo, this));
	}
	else if( name == "health" )
	{
		features[typeid(FeatureHealth).name()].reset(new FeatureHealth(featureInfo, this));
	}
	else if( name == "attack" )
	{
		features[typeid(FeatureAttack).name()].reset(new FeatureAttack(featureInfo, this));
	}
	// else ?
}

void Enti::Tick(const float seconds)
{
	for( list<Feature*>::iterator itFeature = passiveTickFeatures.begin();
			itFeature != passiveTickFeatures.end(); )
	{
		if( !(*itFeature)->Tick(seconds) )
		{
			passiveTickFeatures.erase(itFeature++); // removing from Tick queue
		}
		else
		{
			++itFeature;
		}
	}
	if( tickFeature )
	{		
		if( !tickFeature->Tick(seconds) )
		{
			if( isLastFeature )
				tickFeature = 0;
			else
				isLastFeature = true;
		}
	}
	entiSlot->OnTick(seconds);
}

void Enti::AssignTickFeature(Feature *feature, bool isPassive)
{
	if( isPassive )
	{
		passiveTickFeatures.push_back(feature);
	}
	else
	{
		if( tickFeature )
			tickFeature->Stop();

		tickFeature = feature;
		isLastFeature = false; // do not remove tickFeature
	}
}

}