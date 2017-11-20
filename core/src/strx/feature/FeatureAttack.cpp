#include <strx/entity/Enti.h>
#include <strx/entity/EntiSlot.h>
#include <strx/feature/FeatureInfo.h>

#include "FeatureAttack.h"

namespace strx
{

FeatureAttack::FeatureAttack(const FeatureInfo* featureInfo, Enti* enti)
		: Feature(enti), featureInfoAttack(dynamic_cast<const FeatureInfoAttack*>(featureInfo)), hitProgress(0)
{}

bool FeatureAttack::Attack(s_p<Enti> target)
{
	if (target.get() == enti)
	{
		// Log ( do not attak yourself ) :-)
		return false;
	}
	
	// Try move and set OnComplete for this
	if (!enti->Do<FeatureMove>()->Move(target->GetCoord(), this))
		return false;
	
	this->target = target;
	return true;
}

bool FeatureAttack::Tick(float seconds)
{
	if (hitProgress < 1) // Preparing for 1 hit
	{
		hitProgress += seconds * featureInfoAttack->speed;
		enti->GetSlot().OnAttack();
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
			return false;
		}
	}
	return true;
}

void FeatureAttack::Stop()
{
	enti->GetSlot().OnAttackStop();
	target.reset();
}

void FeatureAttack::OnComplete(bool isComplete)
{
	if (!isComplete)
		return;
	
	enti->GetSlot().OnAttackStart();
	enti->AssignTickFeature(this);
}

}
