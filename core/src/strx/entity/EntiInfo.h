#ifndef _ENTIINFO_H
#define    _ENTIINFO_H

#include <strx/feature/FeatureInfo.h>
#include <strx/common/Resources.h>
#include <Strategix_Forward.h>


namespace strx
{

struct EntiInfo
{
	string name;
	string kind; // building or entity
	u_p<Resources> resources;
	vector<string> depends;
	vector<string> provides;
	
	using FeatureInfosType = umap<string, u_p<FeatureInfo>>;
	FeatureInfosType featureInfos;
	
	
	EntiInfo() : resources(new Resources()) {}
	
	EntiInfo(const EntiInfo& other)
			: name(other.name)
			, kind(other.kind)
			, resources(new Resources(*other.resources))
			, depends(other.depends)
			, provides(other.provides)
	{
		for (const auto& pa : other.featureInfos)
		{
			featureInfos[pa.first].reset(pa.second->clone());
		}
	}
	
	EntiInfo& operator=(const EntiInfo&) = delete;
	
	u_p<EntiInfo> clone() const { return make_u<EntiInfo>(*this); }
};
}

#endif    /* _ENTIINFO_H */

