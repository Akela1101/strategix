/* 
 * File:   FeatureHealth.cpp
 * Author: Akela1101
 * 
 * Created on 3 Июнь 2011 г., 13:14
 */

#include "Enti.h"
#include "EntiSlot.h"
#include "FeatureInfo.h"

#include "FeatureHealth.h"


namespace Strategix
{

FeatureHealth::FeatureHealth(const FeatureInfo *featureInfo, Enti *enti)
	:
	Feature(enti),
	featureInfoHealth(dynamic_cast<const FeatureInfoHealth*>(featureInfo)),	
	hp(featureInfoHealth->hp)
{}

bool FeatureHealth::Tick(const float seconds)
{
	// regeneration. if integer value changes -> OnHpChange
	return true;
}

void FeatureHealth::Stop()
{
	// Stop Regeneration
}

const HpType FeatureHealth::GetMaxHp() const
{
	return featureInfoHealth->hp;
}

bool FeatureHealth::HpChange(const HpType deltaHp)
{
	hp += deltaHp;	
	
	if( (int)hp <= 0 )
	{
		// Dead
		hp = 0;
		enti->entiSlot->OnHpChange();
		return false;
	}
	else if ( hp > featureInfoHealth->hp )
	{
		// Stop healing|repair
		hp = featureInfoHealth->hp;
	}
	enti->entiSlot->OnHpChange();	
	return true;
}

}
