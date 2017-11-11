#ifndef _ENTIINFO_H
#define    _ENTIINFO_H

#include "FeatureInfo.h"
#include "Resources.h"

#include <map>
#include <string>
#include <vector>

#include "Strategix_Forward.h"


namespace Strategix
{
using namespace std;

struct EntiInfo
{
	string name;
	string kind; // building or entiSlot
	u_p<Resources> resources;
	vector<string> depends;
	vector<string> provides;
	
	typedef map<string, s_p<FeatureInfo>> FeatureInfosType;
	FeatureInfosType featureInfos;
	
	
	EntiInfo() : resources(Kernel::MakeResources()) {}
	
	EntiInfo(const EntiInfo& _c)
			: name(_c.name)
			, kind(_c.kind)
			, resources(new Resources(*_c.resources))
			, depends(_c.depends)
			, provides(_c.provides)
	{
		for (const auto& pa : _c.featureInfos)
		{
			featureInfos[pa.first].reset(pa.second->copy());
		}
	}
	
	EntiInfo& operator=(const EntiInfo& _c) = delete;
	
	virtual ~EntiInfo() = default;
	
	virtual EntiInfo* clone() const { return new EntiInfo(*this); }
};
}

#endif    /* _ENTIINFO_H */

