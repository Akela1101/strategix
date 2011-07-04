/* 
 * File:   FeatureAttack.h
 * Author: Akela1101
 *
 * Created on 3 Июнь 2011 г., 16:17
 */

#ifndef _FEATUREATTACK_H
#define	_FEATUREATTACK_H

#include "Feature.h"
#include "Interfaces.h"

#include "Strategix_Forward.h"


namespace Strategix
{
	class FeatureAttack : public Feature, public ICommand
	{
	protected:
		const FeatureInfoAttack *featureInfoAttack; // Link to tree
		
	private:
		Enti *target;
		HpType hitProgress;

	public:
		FeatureAttack(const FeatureInfo *featureInfo, Enti *enti);
		
		bool Attack(Enti *target);
		virtual bool Tick(const float seconds);
		virtual void Stop();

		virtual void OnComplete(bool isComplete); // Moving Complete

	protected:

	private:
		FeatureAttack(const FeatureAttack &_c);
		FeatureAttack& operator =(const FeatureAttack &_c);
	};
}

#endif	/* _FEATUREATTACK_H */

