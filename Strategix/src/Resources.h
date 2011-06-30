/* 
 * File:   Resources.h
 * Author: Akela1101
 *
 * Created on 17 Май 2011 г., 10:52
 */

#ifndef _RESOURCES_H
#define	_RESOURCES_H

#include "Resource.h"

#include <map>
#include <string>
#include <algorithm>


namespace Strategix
{
	using namespace std;

	class Resources
	{
		friend class KernelBase;

		map<string, float> values;
	
	public:
		Resources(const Resources &_c) { init(_c); }
		Resources& operator =(const Resources &_c) { if( this != &_c ) init(_c);   return *this; }

		// Get @#~ Needless?
		const map<string, float> &Get() { return values; }

		// Get resource by name
		float& at(const string resourceName)
		{
			return values.find(resourceName)->second; // never throws
		}
		const float& at(const string resourceName) const
		{
			return values.find(resourceName)->second; // never throws
		}

		// with Resource
		Resources operator +(const Resource &resource) const
		{
			Resources new_r = *this;
			new_r.at(resource.value.first) += resource.value.second;
			return new_r;
		}
		Resources operator -(const Resource &resource) const
		{
			Resources new_r = *this;
			new_r.at(resource.value.first) -= resource.value.second;
			return new_r;
		}
		Resources& operator +=(const Resource &resource)
		{
			this->at(resource.value.first) += resource.value.second;
			return *this;
		}
		Resources& operator -=(const Resource &resource)
		{
			this->at(resource.value.first) -= resource.value.second;
			return *this;
		}

		// with other Resources
		Resources operator +(const Resources &_r) const
		{
			Resources new_r;
			map<string, float>::const_iterator iValue1 = values.begin();
			map<string, float>::const_iterator iValue2 = _r.values.begin();
			
			for( ; iValue1 != values.end(); ++iValue1, ++iValue2 )
			{
				new_r.values.insert(make_pair(iValue1->first, iValue1->second + iValue2->second));
			}
			return new_r;
		}
//		Resources operator -(const Resources &_r) const
//		{
//			Resources new_r;
//			transform(values.begin(), values.end(),
//				_r.values.begin(), new_r.values.begin(), opSub());
//			return new_r;
//		}
//		Resources& operator +=(const Resources &_r)
//		{
//			transform(values.begin(), values.end(),
//				_r.values.begin(), values.begin(), opAdd());
//			return *this;
//		}
//		Resources& operator -=(const Resources &_r)
//		{
//			transform(values.begin(), values.end(),
//				_r.values.begin(), values.begin(), opSub());
//			return *this;
//		}

//		Resources operator -()
//		{
//			Resources new_r;
//			transform(values.begin(), values.end(), new_r.values.begin(), opMinus());
//			return new_r;
//		}

	private:
		Resources() {}
		void init(const Resources &_c) { values = _c.values; }

//		struct opAdd { int operator() (const Resource::PairType i, const Resource::PairType j) { return i.second + j.second; } };
//		struct opSub { int operator() (const Resource::PairType i, const Resource::PairType j) { return i.second - j.second; } };
//		struct opMinus { int operator() (Resource::PairType i) { return -i.second; } };
	};
}

#endif	/* _RESOURCES_H */

