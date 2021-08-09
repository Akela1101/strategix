#pragma once

#include "Resources.hpp"
#include "strx_fwd.hpp"


namespace strx
{
// Global feature properties

struct FeatureInfo : boost::noncopyable
{
	FeatureInfo() = default;
	virtual ~FeatureInfo() = default;
	virtual FeatureInfo* clone() = 0;
};

struct HealthFeatureInfo : FeatureInfo
{
	HpType hp;       ///< hit points
	float recovery;  ///< hp/sec recovery speed

	HealthFeatureInfo(const HpType hp, float recovery) : hp(hp), recovery(recovery) {}
	HealthFeatureInfo* clone() override { return new HealthFeatureInfo(hp, recovery); }
};

struct MoveFeatureInfo : FeatureInfo
{
	float speed;  ///< tile/sec

	MoveFeatureInfo(float speed) : speed(speed) {}
	MoveFeatureInfo* clone() override { return new MoveFeatureInfo(speed); }
};

struct AttackFeatureInfo : FeatureInfo
{
	HpType damage;  ///< hp reduced on one attack
	float speed;    ///< hit/sec
	float radius;   ///< reach radius

	AttackFeatureInfo(const HpType damage, float speed, float radius) : damage(damage), speed(speed), radius(radius) {}
	AttackFeatureInfo* clone() override { return new AttackFeatureInfo(damage, speed, radius); }
};

struct CollectFeatureInfo : FeatureInfo
{
	float speed;                ///< amount/sec
	float radius;               ///< reach radius
	u_p<Resources> capacities;  // maximum amout of each resource, entity can bear

	CollectFeatureInfo(float speed, float radius, u_p<Resources> capacities)
	        : speed(speed), radius(radius), capacities(move(capacities))
	{}
	CollectFeatureInfo* clone() override
	{
		return new CollectFeatureInfo(speed, radius, make_u<Resources>(*capacities));
	}
};

}  // namespace strx
