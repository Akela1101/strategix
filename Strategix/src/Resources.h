/* 
 * File:   Resources.h
 * Author: Akela1101
 *
 * Created on 17 Май 2011 г., 10:52
 */

#ifndef _RESOURCES_H
#define	_RESOURCES_H

#include "StrategixCommon.h"

#include <vector>
#include <string>
#include <algorithm>


namespace Strategix
{
	using namespace std;

	class Resources
	{
		vector<ResType> resources;
		
	private:
		struct opAdd { int operator() (ResType i, ResType j) { return i + j; } };
		struct opSub { int operator() (ResType i, ResType j) { return i - j; } };
		struct opMinus { int operator() (ResType i) { return -i; } };
		struct isNeg { bool operator() (ResType i) { return i < 0; } };

	public:
		// Криво, блин =__=
		Resources();
		Resources(const int index, const ResType res);

		Resources(const Resources &_c);
		Resources & operator =(const Resources &_c);

		// Get resource by name
		ResType& operator() (const string resourceName);
		const ResType& operator() (const string resourceName) const;

		Resources operator +(const Resources &_r) const
		{
			Resources new_r;
			transform(resources.begin(), resources.end(),
				_r.resources.begin(), new_r.resources.begin(), opAdd());
			return new_r;
		}

		Resources operator -(const Resources &_r) const
		{
			Resources new_r;
			transform(resources.begin(), resources.end(),
				_r.resources.begin(), new_r.resources.begin(), opSub());
			return new_r;
		}

		Resources& operator +=(const Resources &_r)
		{
			transform(resources.begin(), resources.end(),
				_r.resources.begin(), resources.begin(), opAdd());
			return *this;
		}

		Resources& operator -=(const Resources &_r)
		{
			transform(resources.begin(), resources.end(),
				_r.resources.begin(), resources.begin(), opSub());
			return *this;
		}

		Resources operator -()
		{
			Resources new_r;
			transform(resources.begin(), resources.end(), new_r.resources.begin(), opMinus());
			return new_r;
		}

		bool isNegative()
		{
			if( resources.end() == find_if(resources.begin(), resources.end(), isNeg()) )
				return false;
			return true;
		}

	private:
		inline void init(const Resources &_c);
	};
}

#endif	/* _RESOURCES_H */

