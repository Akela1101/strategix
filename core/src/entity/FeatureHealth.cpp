#include "../../strx/Entity.hpp"
#include "../../strx/FeatureInfo.hpp"
#include "../../strx/Kernel.hpp"
#include "../../strx/Message.hpp"
#include "../game/GameKernel.hpp"
#include "../game/PlayerKernel.hpp"
#include "EntityKernel.hpp"

#include "FeatureHealth.hpp"

namespace strx
{

FeatureHealth::FeatureHealth(const FeatureInfo* featureInfo, EntityKernel* entity)
        : Feature(entity), info(dynamic_cast<const HealthFeatureInfo*>(featureInfo)), hp(info->hp)
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
	if (hp == 0) return false;  // prevent destroing more than once

	hp += deltaHp;

	if (hp <= 0)
	{
		hp = 0;  // destroied
		entity->GetGame().RemoveEntity(entity->GetId());
	}
	else if (hp > info->hp)
	{
		hp = info->hp;  // stop recovery
	}
	Kernel::SendMessageAll(make_s<HpMessage>(entity->GetId(), hp));
	return hp != 0;
}

}  // namespace strx
