#ifndef _RESOURCES_H
#define    _RESOURCES_H

#include <algorithm>
#include <strx/common/Resource.h>


namespace strx
{
struct Resources : ResourcesType
{	
	// with one Resource
	Resources operator+(const Resource& resource) const
	{
		Resources out = *this;
		out[resource.first] += resource.second;
		return out;
	}
	
	Resources operator-(const Resource& resource) const
	{
		Resources out = *this;
		out[resource.first] -= resource.second;
		return out;
	}
	
	Resources& operator+=(const Resource& resource)
	{
		operator[](resource.first) += resource.second;
		return *this;
	}
	
	Resources& operator-=(const Resource& resource)
	{
		operator[](resource.first) -= resource.second;
		return *this;
	}
	
	// with multiple Resources
	Resources operator+(const Resources& other) const
	{
		Resources out;
		for (auto resource : *this)
		{
			auto it = other.find(resource.first);
			ResourceUnit otherAmount = it != other.end() ? it->second : 0;
			out.emplace(resource.first, resource.second + otherAmount);
		}
		return out;
	}
};
}

#endif    /* _RESOURCES_H */

