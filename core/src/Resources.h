#ifndef _RESOURCES_H
#define    _RESOURCES_H

#include "Resource.h"
#include "Kernel.h"

#include <algorithm>
#include <utility>


namespace strategix
{
using namespace std;

class Resources
{
	ResourcesAllType values; // TODO: move constr

public:
	Resources() = default;
	
	Resources(const Resources& _c) : values(_c.values) {}
	
	Resources(ResourcesAllType values) : values(move(values)) {}
	
	Resources& operator=(const Resources& _c)
	{
		if (this != &_c) values = _c.values;
		return *this;
	}
	
	// Get @#~ Needless?
	const ResourcesAllType& Get() { return values; }
	
	// Get resource by name
	const Resource at(const string& resourceName) const
	{
		return *values.find(resourceName); // never throws
	}
	
	// with Resource
	Resources operator+(const Resource& resource) const
	{
		Resources new_r = *this;
		new_r.set(resource.value->first) += resource.value->second;
		return new_r;
	}
	
	Resources operator-(const Resource& resource) const
	{
		Resources new_r = *this;
		new_r.set(resource.value->first) -= resource.value->second;
		return new_r;
	}
	
	Resources& operator+=(const Resource& resource)
	{
		this->set(resource.value->first) += resource.value->second;
		return *this;
	}
	
	Resources& operator-=(const Resource& resource)
	{
		this->set(resource.value->first) -= resource.value->second;
		return *this;
	}
	
	// with other Resources
	Resources operator+(const Resources& _r) const
	{
		Resources new_r;
		auto iValue1 = values.begin();
		auto iValue2 = _r.values.begin();
		
		for (; iValue1 != values.end(); ++iValue1, ++iValue2)
		{
			new_r.values.insert(make_pair(iValue1->first, iValue1->second + iValue2->second));
		}
		return new_r;
	}

private:
	// for convenience inside the class
	float& set(const string& resourceName) { return values.find(resourceName)->second; }
};
}

#endif    /* _RESOURCES_H */

