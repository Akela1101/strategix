#include <strx/entity/Entity.h>
#include <strx/entity/EntitySlot.h>
#include <strx/feature/FeatureInfo.h>
#include <strx/game/Game.h>
#include <strx/player/Player.h>

#include "FeatureHealth.h"

namespace strx
{

FeatureHealth::FeatureHealth(const FeatureInfo* featureInfo, Entity* entity)
        : Feature(entity), info(dynamic_cast<const HealthFeatureInfo*>(featureInfo))
        , hp(info->hp)
{}

void FeatureHealth::Tick(float seconds)
{
	//@#~ recovery
}

const HpType FeatureHealth::GetMaxHp() const
{
	return info->hp;
}

bool FeatureHealth::ChangeHp(HpType deltaHp)
{
	hp += deltaHp;

	if (hp <= 0)
	{
		hp = 0; // destroied
		entity->GetGame().RemoveEntity(entity->GetId());
	}
	else if (hp > info->hp)
	{
		hp = info->hp; // stop recovery
	}
	//@#~entity->GetSlot().OnHpChange();
	return hp != 0;
}

}
