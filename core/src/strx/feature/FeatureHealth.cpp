#include <strx/entity/Entity.h>
#include <strx/entity/EntitySlot.h>
#include <strx/feature/FeatureInfo.h>
#include <strx/player/Player.h>

#include "FeatureHealth.h"

namespace strx
{

FeatureHealth::FeatureHealth(const FeatureInfo* featureInfo, Entity* entity)
		: Feature(entity), featureInfoHealth(dynamic_cast<const FeatureInfoHealth*>(featureInfo))
		, hp(featureInfoHealth->hp)
{}

void FeatureHealth::Tick(float seconds)
{
	// regeneration. if integer value changes -> OnHpChange
}

void FeatureHealth::Stop()
{
	// Stop Regeneration
}

const HpType FeatureHealth::GetMaxHp() const
{
	return featureInfoHealth->hp;
}

bool FeatureHealth::HpChange(HpType deltaHp)
{
	hp += deltaHp;
	
	if (hp <= 0)
	{
		// Dead
		hp = 0;
		entity->GetSlot().OnHpChange();
		entity->GetPlayer().RemoveEntity(entity);
		return false;
	}
	else if (hp > featureInfoHealth->hp)
	{
		// Stop healing|repair
		hp = featureInfoHealth->hp;
	}
	entity->GetSlot().OnHpChange();
	return true;
}

}
