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

Enti::Enti(const EntiInfo *ei, const MapCoord &mapCoord)
	:
	ei(ei),
	coord(mapCoord)
{
}

Enti::~Enti()
{
}

void Enti::Tick(const float seconds)
{
	foreach(Feature* feature, tickFeatures)
	{
		feature->Tick(seconds);
	}
	unit->OnTick(seconds);
}

FeatureMove& Enti::Move()
{
	return dynamic_cast<FeatureMove&>(GetFeature("move"));
}

Feature& Enti::GetFeature(const string &name)
{
	FeaturesType::iterator feature = features.find(name);
	if( feature != features.end() )
	{
		return *feature->second;
	}
	else
	{
		STRATEGIX_ERROR(string("There is no feature named: ") + name);
	}
}

}