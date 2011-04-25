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
	struct FeatureInfo
	{
		virtual ~FeatureInfo() {}
		virtual void abstract() = 0;
	};

	struct FeatureInfoIdle : FeatureInfo
	{
		virtual ~FeatureInfoIdle() {}
	};

	struct FeatureInfoMove : FeatureInfo
	{
		float speed;
		//
		virtual ~FeatureInfoMove() {}
	};

	struct FeatureInfoHealth : FeatureInfo
	{
		float hp;
		float regenSpeed;
		//
		virtual ~FeatureInfoHealth() {}
	};
}

#endif	/* _FEATUREINFO_H */

