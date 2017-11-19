#ifndef _FEATUREHEALTH_H
#define    _FEATUREHEALTH_H

#include "Feature.h"

#include "common/Strategix_Forward.h"


namespace strategix
{
class FeatureHealth : public Feature
{
protected:
	const FeatureInfoHealth* featureInfoHealth; // Link to tree

private:
	HpType hp;

public:
	FeatureHealth(const FeatureInfo* featureInfo, Enti* enti);
	FeatureHealth(const FeatureHealth& _c) = delete;
	FeatureHealth& operator=(const FeatureHealth& _c) = delete;
	
	bool Tick(float seconds) override;
	void Stop() override;
	
	const HpType GetHp() const { return hp; }
	
	const HpType GetMaxHp() const;
	bool HpChange(HpType deltaHp); // false if become dead
};
}

#endif    /* _FEATUREHEALTH_H */

