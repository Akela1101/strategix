/* 
 * File:   Resource.h
 * Author: Akela1101
 *
 * Created on 29 Июнь 2011 г., 13:49
 */

#ifndef _RESOURCE_H
#define	_RESOURCE_H

#include "StrategixError.h"

#include <utility>
#include <string>


namespace Strategix
{
	using namespace std;

	class Resource
	{
		friend class KernelBase;
		friend class Resources;

		typedef pair<string, float> PairType;
		PairType value;
		
	public:
		Resource(const Resource &_c) { init(_c); }
		Resource& operator =(const Resource &_c) { if( this != &_c ) init(_c);   return *this; }

		operator float&() { return value.second; }
		operator const float&() const { return value.second; }

		Resource operator +(const Resource &resource) const
		{
			if( value.first != resource.value.first )
				STRATEGIX_ERROR("Trying addition resources with different types: "
				                + value.first + " & " + resource.value.first);
			return Resource(value.first, value.second + resource.value.second);
		}
		Resource operator -(const Resource &resource) const
		{
			if( value.first != resource.value.first )
				STRATEGIX_ERROR("Trying subtraction resources with different types: "
				                + value.first + " & " + resource.value.first);
			return Resource(value.first, value.second + resource.value.second);
		}
		Resource& operator +=(const Resource &resource)
		{
			if( value.first != resource.value.first )
				STRATEGIX_ERROR("Trying addition resources with different types: "
				                + value.first + " & " + resource.value.first);
			value.second += resource.value.second;
			return *this;
		}
		Resource& operator -=(const Resource &resource)
		{
			if( value.first != resource.value.first )
				STRATEGIX_ERROR("Trying subtraction resources with different types: "
				                + value.first + " & " + resource.value.first);
			value.second -= resource.value.second;
			return *this;
		}

	private:
		Resource(const string name, const float resource) : value(name, resource) {}		
		void init(const Resource &_c) { value = _c.value; }
	};
}

#endif	/* _RESOURCE_H */

