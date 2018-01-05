#pragma once

#include <strx/common/Resource.h>


namespace strx
{
struct Resources : ResourcesType
        , boost::additive<Resources, Resource
        , boost::addable<Resources>>
{
	using ResourcesType::ResourcesType;

	Resources& operator+=(const Resource& resource) { (*this)[resource.first] += resource.second; return *this; }
	Resources& operator-=(const Resource& resource) { (*this)[resource.first] -= resource.second; return *this; }

	// with multiple Resources
	Resources& operator+=(const Resources& other)
	{
		for (auto resource : *this)
		{
			auto it = other.find(resource.first);
			if (it != other.end())
				emplace(resource.first, resource.second + it->second);
		}
		return *this;
	}
};
}
