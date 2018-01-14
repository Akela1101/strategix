#include <strx/entity/Entity.h>
#include <strx/entity/EntitySlot.h>
#include <strx/feature/FeatureInfo.h>
#include <strx/feature/FeatureHealth.h>
#include <strx/feature/FeatureMove.h>
#include <strx/game/Game.h>
#include <strx/player/Player.h>

#include "FeatureAttack.h"

namespace strx
{

FeatureAttack::FeatureAttack(const FeatureInfo* featureInfo, Entity* entity)
        : Feature(entity)
        , info(dynamic_cast<const AttackFeatureInfo*>(featureInfo))
{}

bool FeatureAttack::Attack(IdType targetId)
{
	target = entity->GetGame().GetEntity(targetId);
	if (!target) return false;

	if (&target->GetPlayer() == &entity->GetPlayer())
	{
		error_log << "Attacking own units is not supported yet.";
		return false;
	}

	hitProgress = 1.0; // first hit is instant, if near the target

	entity->AssignTask(this);
	return true;
}

void FeatureAttack::Tick(float seconds)
{
	// prepare for a hit
	if (hitProgress < 1)
	{
		hitProgress += seconds * info->speed;
		return;
	}

	// check it's not destroied
	if (target->GetHp() == 0)
	{
		entity->AssignTask(nullptr);
		return;
	}

	// pursue the target
	if ((entity->GetMapCoord() - target->GetMapCoord()).Len() > info->radius)
	{
		entity->Do<FeatureMove>().Move(target, info->radius, this);
		return;
	}

	// one hit
	--hitProgress;
	if (!target->Do<FeatureHealth>().ChangeHp(-info->damage))
	{
		entity->AssignTask(nullptr); // target destroied
	}
}

void FeatureAttack::Stop()
{
	movingTarget = target;
	target.reset();
}

void FeatureAttack::Completed(bool done)
{
	if (!done) return;

	if (target = movingTarget.lock())
	{
		entity->AssignTask(this);
	}
}

}
