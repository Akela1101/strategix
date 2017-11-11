#ifndef _RESOURCE_H
#define    _RESOURCE_H

#include <utility>
#include <map>
#include <string>


namespace Strategix
{
using namespace std;

typedef map<string, float> ResourcesAllType;
typedef pair<string, float> ResourceValueType; // not ResourcesAllType::value_type

class Resource
{
	friend class KernelBase;
	
	friend class Resources;
	
	ResourceValueType value;

public:
	Resource(const Resource& _c) { init(_c.value); }
	
	Resource(const ResourcesAllType::value_type& _pa) { init(_pa); }
	
	Resource& operator=(const Resource& _c)
	{
		if (this != &_c) init(_c.value);
		return *this;
	}
	
	Resource& operator=(const ResourceValueType& _pa)
	{
		init(_pa);
		return *this;
	}
	
	operator float&() { return value.second; }
	
	operator const float&() const { return value.second; }
	
	operator const string() const { return value.first; }
	
	// With no resource type check !!!
	const Resource operator+(const float amount) const
	{
		return Resource(value.first, value.second + amount);
	}
	
	const Resource operator-(const float amount) const
	{
		return Resource(value.first, value.second - amount);
	}
	
	Resource& operator+=(const float amount)
	{
		value.second += amount;
		return *this;
	}
	
	Resource& operator-=(const float amount)
	{
		value.second -= amount;
		return *this;
	}

//		Resource operator +(const Resource &resource) const
//		{
//			if( value.first != resource.value.first )
//				STRATEGIX_EXCEPTION("Trying addition resources with different types: "
//				                + value.first + " & " + resource.value.first);
//			return Resource(value.first, value.second + resource.value.second);
//		}
//		Resource operator -(const Resource &resource) const
//		{
//			if( value.first != resource.value.first )
//				STRATEGIX_EXCEPTION("Trying subtraction resources with different types: "
//				                + value.first + " & " + resource.value.first);
//			return Resource(value.first, value.second - resource.value.second);
//		}
//		Resource& operator +=(const Resource &resource)
//		{
//			if( value.first != resource.value.first )
//				STRATEGIX_EXCEPTION("Trying addition resources with different types: "
//				                + value.first + " & " + resource.value.first);
//			value.second += resource.value.second;
//			return *this;
//		}
//		Resource& operator -=(const Resource &resource)
//		{
//			if( value.first != resource.value.first )
//				STRATEGIX_EXCEPTION("Trying subtraction resources with different types: "
//				                + value.first + " & " + resource.value.first);
//			value.second -= resource.value.second;
//			return *this;
//		}

private:
	Resource(string name, float resource) : value(name, resource) {}
	
	void init(const ResourcesAllType::value_type& _pa) { value = _pa; }
};
}

#endif    /* _RESOURCE_H */

