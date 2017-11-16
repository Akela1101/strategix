#ifndef _ENTIINFO_H
#define    _ENTIINFO_H

#include "FeatureInfo.h"
#include "Resources.h"

#include <unordered_map>
#include <string>
#include <vector>

#include "Strategix_Forward.h"


namespace strategix
{
using namespace std;

struct EntiInfo
{
	string name;
	string kind; // building or entity
	u_p<Resources> resources;
	vector<string> depends;
	vector<string> provides;
	
	using FeatureInfosType = umap<string, u_p<FeatureInfo>>;
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
			featureInfos[pa.first].reset(pa.second->clone());
		}
	}
	
	EntiInfo& operator=(const EntiInfo& _c) = delete;
	
	u_p<EntiInfo> clone() const { return make_u<EntiInfo>(*this); }
};
}

#endif    /* _ENTIINFO_H */

