#ifndef _FEATUREINFO_H
#define    _FEATUREINFO_H

#include "strx/common/Resources.h"

#include "Strategix_Forward.h"


namespace strx
{
// Global feature properties

struct FeatureInfo : boost::noncopyable
{
	FeatureInfo() = default;
	virtual ~FeatureInfo() = default;
	virtual FeatureInfo* clone() = 0;
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
	float radius; // radius Entity is able to collect from
	u_p<Resources> capacities; // Maximum amout of each resource, creature can bear
	
	FeatureInfoCollect(float speed, float radius, u_p<Resources> capacities)
			: speed(speed), radius(radius), capacities(move(capacities)) {}
	
	FeatureInfoCollect* clone() override { return new FeatureInfoCollect(speed, radius, make_u<Resources>(*capacities)); }
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

