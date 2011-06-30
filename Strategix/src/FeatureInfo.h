/* 
 * File:   FeatureInfo.h
 * Author: Akela1101
 *
 * Created on 21 Апрель 2011 г., 14:18
 */

#ifndef _FEATUREINFO_H
#define	_FEATUREINFO_H

#include "Strategix_Forward.h"


namespace Strategix
{
	// Global feature properties

	struct FeatureInfo
	{
		FeatureInfo() {}
		virtual ~FeatureInfo() {}
		virtual FeatureInfo* copy() = 0;

	private:
		FeatureInfo(const FeatureInfo &_c);
		FeatureInfo& operator =(const FeatureInfo &_c);
	};

	struct FeatureInfoMove : FeatureInfo
	{
		float speed;

		FeatureInfoMove(const float speed) : speed(speed) {}
		virtual ~FeatureInfoMove() {}
		virtual FeatureInfoMove* copy() { return new FeatureInfoMove(speed); }
	};

	struct FeatureInfoCollect : FeatureInfo
	{
		float speed; // Res/sec
		float radius; // radius Enti is able to collect from
		float capacity;

		FeatureInfoCollect(const float speed, const float radius, const float capacity)
			: speed(speed), radius(radius), capacity(capacity) {}
		virtual ~FeatureInfoCollect() {}
		virtual FeatureInfoCollect* copy() { return new FeatureInfoCollect(speed, radius, capacity); }
	};

	struct FeatureInfoHealth : FeatureInfo
	{
		HpType hp;
		float regenSpeed;
		
		FeatureInfoHealth(const HpType hp, const float regenSpeed)
			: hp(hp), regenSpeed(regenSpeed) {}
		virtual ~FeatureInfoHealth() {}
		virtual FeatureInfoHealth* copy() { return new FeatureInfoHealth(hp, regenSpeed); }
	};

	struct FeatureInfoAttack : FeatureInfo
	{
		HpType damage;
		float speed; // Hit/sec

		FeatureInfoAttack(const HpType damage, const float speed)
			: damage(damage), speed(speed) {}
		virtual ~FeatureInfoAttack() {}
		virtual FeatureInfoAttack* copy() { return new FeatureInfoAttack(damage, speed); }
	};
}

#endif	/* _FEATUREINFO_H */

