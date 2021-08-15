#pragma once

#include <boost/operators.hpp>
#include <nya.hpp>
#include <string>
#include <unordered_map>

namespace strx
{
using ResourceUnit = int;
using ResourcesType = umap<std::string, ResourceUnit>;
using ResourceType = ResourcesType::value_type;

struct Resource
        : public ResourceType
        , boost::additive<Resource, ResourceUnit>
{
	using ResourceType::ResourceType;
	Resource(const ResourceType& other) : ResourceType(other) {}

	const std::string& GetName() const { return first; }
	operator ResourceUnit&() { return second; }
	operator ResourceUnit() const { return second; }

	// With no resource type check !!!
	Resource& operator+=(ResourceUnit amount) { return second += amount, *this; }
	Resource& operator-=(ResourceUnit amount) { return second -= amount, *this; }
};
}  // namespace strx
