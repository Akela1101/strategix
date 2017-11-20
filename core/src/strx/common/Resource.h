#ifndef _RESOURCE_H
#define    _RESOURCE_H

#include <strx/common/Strategix_Forward.h>


namespace strx
{

using ResourceUnit = int;
using ResourcesType = umap<string, ResourceUnit>;
using ResourceType = ResourcesType::value_type;

struct Resource : public ResourceType
{
	using ResourceType::ResourceType;
	Resource(const ResourceType& other) : ResourceType(other) {}
	
	const string& GetName() const { return first; }
	operator ResourceUnit&() { return second; }
	operator ResourceUnit() const { return second; }
	
	// With no resource type check !!!
	const Resource operator+(ResourceUnit amount) const
	{
		return Resource(first, second + amount);
	}
	
	const Resource operator-(ResourceUnit amount) const
	{
		return Resource(first, second - amount);
	}
	
	Resource& operator+=(ResourceUnit amount)
	{
		second += amount;
		return *this;
	}
	
	Resource& operator-=(ResourceUnit amount)
	{
		second -= amount;
		return *this;
	}
};
}

#endif    /* _RESOURCE_H */

