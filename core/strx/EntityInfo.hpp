#pragma once

#include "FeatureInfo.hpp"
#include "Resources.hpp"
#include "strx_fwd.hpp"


namespace strx
{

struct EntityInfo
{
	string name;
	string kind;  // building or entity
	u_p<Resources> resources;
	vector<string> depends;
	vector<string> provides;

	using FeatureInfosType = umap<string, u_p<FeatureInfo>>;
	FeatureInfosType featureInfos;


	EntityInfo() : resources(new Resources()) {}

	EntityInfo(const EntityInfo& other)
	        : name(other.name)
	        , kind(other.kind)
	        , resources(new Resources(*other.resources))
	        , depends(other.depends)
	        , provides(other.provides)
	{
		for (const auto& pa : other.featureInfos) featureInfos[pa.first].reset(pa.second->clone());
	}

	EntityInfo& operator=(const EntityInfo&) = delete;

	u_p<EntityInfo> clone() const { return make_u<EntityInfo>(*this); }
};
}  // namespace strx
