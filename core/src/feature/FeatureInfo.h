#ifndef _FEATUREINFO_H
#define    _FEATUREINFO_H

#include "common/Resources.h"

#include "common/Strategix_Forward.h"


namespace strategix
{
// Global feature properties

struct FeatureInfo
{
	FeatureInfo() = default;
	
	virtual ~FeatureInfo() = default;
	
	virtual FeatureInfo* clone() = 0;
	
	FeatureInfo(const FeatureInfo& _c) = delete;
	FeatureInfo& operator=(const FeatureInfo& _c) = delete;
};

struct FeatureInfoMove : FeatureInfo
{
	float speed;
	
	FeatureInfoMove(float speed) : speed(speed) {}
	
	FeatureInfoMove* clone() override { return new FeatureInfoMove(speed); }
};

struct FeatureInfoCollect : FeatureInfo
{
	float speed; // Res/sec
	float radius; // radius Enti is able to collect from
	s_p<Resources> capacities; // Maximum amout of each resource, creature can bear
	
	FeatureInfoCollect(float speed, float radius, s_p<Resources> capacities)
			: speed(speed), radius(radius), capacities(capacities) {}
	
	FeatureInfoCollect* clone() override { return new FeatureInfoCollect(speed, radius, capacities); }
};

struct FeatureInfoHealth : FeatureInfo
{
	HpType hp;
	float regenSpeed;
	
	FeatureInfoHealth(const HpType hp, float regenSpeed)
			: hp(hp), regenSpeed(regenSpeed) {}
	
	FeatureInfoHealth* clone() override { return new FeatureInfoHealth(hp, regenSpeed); }
};

struct FeatureInfoAttack : FeatureInfo
{
	HpType damage;
	float speed; // Hit/sec
	
	FeatureInfoAttack(const HpType damage, float speed)
			: damage(damage), speed(speed) {}
	
	FeatureInfoAttack* clone() override { return new FeatureInfoAttack(damage, speed); }
};
}

#endif    /* _FEATUREINFO_H */

