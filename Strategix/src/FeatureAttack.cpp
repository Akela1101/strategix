/* 
 * File:   FeatureAttack.cpp
 * Author: Akela1101
 * 
 * Created on 3 Июнь 2011 г., 16:17
 */

#include "Enti.h"
#include "EntiSlot.h"
#include "FeatureInfo.h"
#include "FeatureMove.h"
#include "FeatureHealth.h"

#include "FeatureAttack.h"


namespace Strategix
{

FeatureAttack::FeatureAttack(const FeatureInfo *featureInfo, Enti *enti)
	:
	Feature(enti),
	featureInfoAttack(dynamic_cast<const FeatureInfoAttack*>(featureInfo)),
	hitProgress(0)
{}

bool FeatureAttack::Attack(sh_p<Enti> target)
{
	if( target.get() == enti )
	{
		// Log ( do not attak yourself ) :-)
		return false;
	}

	// Try move and set OnComplete for this
	if( !enti->Do<FeatureMove>()->Move(target->coord, this) )
		return false;

	this->target = target;
	return true;
}

bool FeatureAttack::Tick(const float seconds)
{
	if( hitProgress < 1 ) // Preparing for 1 hit
	{
		hitProgress += seconds * featureInfoAttack->speed;
		enti->entiSlot->OnAttack();
	}
	else // Inflict damage
	{
		hitProgress = 0;
		if( target->Do<FeatureHealth>()->HpChange(-featureInfoAttack->damage) )
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
	enti->entiSlot->OnAttackStop();
	target.reset();
}

void FeatureAttack::OnComplete(bool isComplete)
{
	if( !isComplete )
		return;

	enti->entiSlot->OnAttackStart();
	enti->AssignTickFeature(this);
}

}
