/* 
 * File:   EntiInfo.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:34
 */

#ifndef _ENTIINFO_H
#define	_ENTIINFO_H

#include "StrategixCommon.h"
#include "FeatureInfo.h"

#include <map>
#include <string>
#include <vector>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;

	struct EntiInfo
	{
		string name;
		string kind; // building or unit
		Resources resources;
		vector<string> depends; 
		vector<string> provides;
		
		typedef map<string, sh_p<FeatureInfo> > FeatureInfosType;
		FeatureInfosType featureInfos;

		EntiInfo() {}
		virtual ~EntiInfo() {}

		// virtual copy constructor
		virtual EntiInfo* copy() const
		{ 
			EntiInfo *copy = new EntiInfo();
			copy->init(*this);
			return copy;
		}

	protected:
		void init(const EntiInfo &_c)
		{
			name = _c.name;
			kind = _c.kind;
			resources = _c.resources;
			depends = _c.depends;
			provides = _c.provides;

			foreach(const FeatureInfosType::value_type &pa, _c.featureInfos)
			{
				featureInfos[pa.first].reset(pa.second->copy());
			}
		}
		
	private: // forbid other copying
		EntiInfo(const EntiInfo &_c);
		EntiInfo& operator =(const EntiInfo &_c);
	};
}

#endif	/* _ENTIINFO_H */

