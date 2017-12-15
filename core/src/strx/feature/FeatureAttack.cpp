#include <strx/entity/Entity.h>
#include <strx/entity/EntitySlot.h>
#include <strx/feature/FeatureInfo.h>
#include <strx/feature/FeatureHealth.h>
#include <strx/feature/FeatureMove.h>

#include "FeatureAttack.h"

namespace strx
{

FeatureAttack::FeatureAttack(const FeatureInfo* featureInfo, Entity* entity)
		: Feature(entity), featureInfoAttack(dynamic_cast<const FeatureInfoAttack*>(featureInfo)), hitProgress(0)
{}

bool FeatureAttack::Attack(s_p<Entity> target)
{
	if (target.get() == entity)
	{
		error_log << "Do not attack yourself :-)";
		return false;
	}
	
	// Try move and set OnComplete for this
	if (!entity->Do<FeatureMove>()->Move(target->GetCoord(), 0, this))
		return false;
	
	this->target = target;
	return true;
}

void FeatureAttack::Tick(float seconds)
{
	if (hitProgress < 1) // Preparing for 1 hit
	{
		hitProgress += seconds * featureInfoAttack->speed;
		entity->GetSlot().OnAttack();
	}
	else // Inflict damage
	{
		hitProgress = 0;
		if (target->Do<FeatureHealth>()->HpChange(-featureInfoAttack->damage))
		{
			// Continue attack
		}
		else // Dead
		{
			Stop();
		}
	}
}

void FeatureAttack::Stop()
{
	entity->GetSlot().OnAttackStop();
	target.reset();
}

void FeatureAttack::OnComplete(bool isComplete)
{
	if (!isComplete)
		return;
	
	entity->GetSlot().OnAttackStart();
	entity->AssignTask(this);
}

}
