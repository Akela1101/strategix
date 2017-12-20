#pragma once

#include <Strategix_Forward.h>
#include <boost/operators.hpp>

namespace strx
{

using ResourceUnit = int;
using ResourcesType = umap<string, ResourceUnit>;
using ResourceType = ResourcesType::value_type;

struct Resource : public ResourceType
		, boost::additive<Resource, ResourceUnit>
{
	using ResourceType::ResourceType;
	Resource(const ResourceType& other) : ResourceType(other) {}
	
	const string& GetName() const { return first; }
	operator ResourceUnit&() { return second; }
	operator ResourceUnit() const { return second; }
	
	// With no resource type check !!!
	Resource& operator +=(ResourceUnit amount) { second += amount; return *this; }
	Resource& operator -=(ResourceUnit amount) { second -= amount; return *this; }
};
}
