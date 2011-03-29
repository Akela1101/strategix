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
	public:
		string name;
		map<string, sh_p<FeatureInfo> > featureInfos;

		// Constant values
		string kind;
		vector<string> depends; 
		vector<string> provides;
		string meshName; 
		float meshScale; // Scale of mesh
		

		// Recreate this as to initialize in constructor ? @#~

		// Derive this class in real Application

	public:
		// ????????????????????????
//		EntiInfo();
//		EntiInfo(const EntiInfo &_c);
//		EntiInfo & operator =(const EntiInfo &_c);
		virtual ~EntiInfo();
	};
}

#endif	/* _ENTIINFO_H */

