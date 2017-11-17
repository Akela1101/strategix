#ifndef _FEATUREATTACK_H
#define    _FEATUREATTACK_H

#include "Feature.h"
#include "Interfaces.h"

#include "Strategix_Forward.h"


namespace strategix
{
class FeatureAttack : public Feature, public ICommand
{
protected:
	const FeatureInfoAttack* featureInfoAttack; // Link to tree

private:
	s_p<Enti> target; // @#~ weak ptr - better ???
	HpType hitProgress;

public:
	FeatureAttack(const FeatureInfo* featureInfo, Enti* enti);
	
	bool Attack(s_p<Enti> target);
	virtual bool Tick(float seconds);
	virtual void Stop();
	
	virtual void OnComplete(bool isComplete); // Moving Complete

protected:

private:
	FeatureAttack(const FeatureAttack& _c);
	FeatureAttack& operator=(const FeatureAttack& _c);
};
}

#endif    /* _FEATUREATTACK_H */

