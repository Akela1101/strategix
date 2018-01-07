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

	hitProgress = 0;

	// move and wait it done
	entity->Do<FeatureMove>().Move(target->GetCoord(), info->radius, this);
	return true;
}

void FeatureAttack::Tick(float seconds)
{
	if (!target) return;

	if (hitProgress < 1) // preparing for hit
	{
		hitProgress += seconds * info->speed;
		return;
	}
	--hitProgress;

	// one hit
	if (!target->Do<FeatureHealth>().ChangeHp(-info->damage))
	{
		entity->AssignTask(nullptr); // target destroied
	}
}

void FeatureAttack::Stop()
{
	target.reset();
}

void FeatureAttack::Completed(bool done)
{
	if (!done) return;

	entity->AssignTask(this);
}

}
