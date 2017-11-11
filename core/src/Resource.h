#ifndef _RESOURCE_H
#define    _RESOURCE_H

#include <utility>
#include <map>
#include <string>
#include <memory>
#include <nya.hpp>


namespace Strategix
{
using namespace std;

using ResourcesAllType = map<string, float>;
using ResourceValueType = ResourcesAllType::value_type; // pair<string, float> ; // not


class Resource
{
	friend class Resources;
	
	u_p<ResourceValueType> value;

public:
	Resource(const string& name, float resource) : value(new ResourceValueType {name, resource}) {}
	
	Resource(const ResourceValueType& _pa) : value(make_u<ResourceValueType>(_pa)) {}
	
	Resource(const Resource& _c) : value(make_u<ResourceValueType>(*_c.value)) {}
	
	Resource& operator=(const ResourceValueType& _pa)
	{
		value = make_u<ResourceValueType>(_pa);
		return *this;
	}
	
	Resource& operator=(const Resource& _c)
	{
		if (this != &_c) value = make_u<ResourceValueType>(*_c.value);
		return *this;
	}
	
	operator float&() { return value->second; }
	
	operator float() const { return value->second; }
	
	operator string() const { return value->first; }
	
	// With no resource type check !!!
	const Resource operator+(const float amount) const
	{
		return Resource(value->first, value->second + amount);
	}
	
	const Resource operator-(const float amount) const
	{
		return Resource(value->first, value->second - amount);
	}
	
	Resource& operator+=(const float amount)
	{
		value->second += amount;
		return *this;
	}
	
	Resource& operator-=(const float amount)
	{
		value->second -= amount;
		return *this;
	}
};
}

#endif    /* _RESOURCE_H */

