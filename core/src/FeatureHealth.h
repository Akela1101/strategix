#ifndef _FEATUREHEALTH_H
#define    _FEATUREHEALTH_H

#include "Feature.h"

#include "Strategix_Forward.h"


namespace Strategix
{
class FeatureHealth : public Feature
{
protected:
	const FeatureInfoHealth* featureInfoHealth; // Link to tree

private:
	HpType hp;

public:
	FeatureHealth(const FeatureInfo* featureInfo, Enti* enti);
	
	virtual bool Tick(const float seconds);
	virtual void Stop();
	
	const HpType GetHp() const
	{ return hp; }
	
	const HpType GetMaxHp() const;
	bool HpChange(const HpType deltaHp); // false if become dead

private:
	FeatureHealth(const FeatureHealth& _c);
	FeatureHealth& operator=(const FeatureHealth& _c);
};
}

#endif    /* _FEATUREHEALTH_H */

