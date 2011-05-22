/* 
 * File:   EntiInfo.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:34
 */

#ifndef _ENTIINFO_H
#define	_ENTIINFO_H

#include "StrategixCommon.h"

#include <map>
#include <string>
#include <vector>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;

	struct FeatureInfo;

	struct EntiInfo
	{
		string name;
		string kind; // @#~ maybe set inplace of string?
		Resources resources;
		vector<string> depends; 
		vector<string> provides;
		
		typedef map<string, sh_p<FeatureInfo> > FeatureInfosType;
		FeatureInfosType featureInfos;

		virtual ~EntiInfo() {}

		virtual EntiInfo *copy() { return new EntiInfo(*this); }
	};
}

#endif	/* _ENTIINFO_H */

