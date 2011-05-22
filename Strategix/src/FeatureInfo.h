/* 
 * File:   FeatureInfo.h
 * Author: Akela1101
 *
 * Created on 21 Апрель 2011 г., 14:18
 */

#ifndef _FEATUREINFO_H
#define	_FEATUREINFO_H

#include "StrategixCommon.h"


namespace Strategix
{
	// Global feature properties

	struct FeatureInfo // Interface
	{
		virtual ~FeatureInfo() {}
	};

	struct FeatureInfoMove : FeatureInfo
	{
		float speed;

		FeatureInfoMove(const float speed) : speed(speed) {}
		virtual ~FeatureInfoMove() {}
	};

	struct FeatureInfoCollect : FeatureInfo
	{
		ResType speed; // Res/sec
		float radius; // radius Enti is able to collect from
		ResType capacity;

		FeatureInfoCollect(const float speed, const float radius, const float capacity)
			: speed(speed), radius(radius), capacity(capacity) {}
		virtual ~FeatureInfoCollect() {}
	};

	struct FeatureInfoHealth : FeatureInfo
	{
		float hp;
		float regenSpeed;
		//
		FeatureInfoHealth(const float hp, const float regenSpeed)
			: hp(hp), regenSpeed(regenSpeed) {}
		virtual ~FeatureInfoHealth() {}
	};
}

#endif	/* _FEATUREINFO_H */

