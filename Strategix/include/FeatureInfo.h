/* 
 * File:   FeatureInfo.h
 * Author: Akela1101
 *
 * Created on 21 Апрель 2011 г., 14:18
 */

#ifndef _FEATUREINFO_H
#define	_FEATUREINFO_H

namespace Strategix
{
	struct FeatureInfo // Interface
	{
		virtual ~FeatureInfo() {}
	};

	struct FeatureInfoMove : FeatureInfo
	{
		float speed;
		//
		//FeatureInfoMove(const FeatureInfoMove &_c) : speed(_c.speed) {}
		FeatureInfoMove(const float speed) : speed(speed) {}
		virtual ~FeatureInfoMove() {}
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

