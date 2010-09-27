/* 
 * File:   EntityInfo.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:34
 */

#ifndef _ENTITYINFO_H
#define	_ENTITYINFO_H

#include <map>
#include <string>

#include "GameStructs.h"

namespace Strategix
{
	using namespace std;

	class EntityInfo
	{
	public:
		string name;
		string kind;
		Resources cost;
		Params params;
		Names depends;
		Names provides;

	public:
		EntityInfo();
		EntityInfo(const EntityInfo &_c);
		EntityInfo & operator =(const EntityInfo &_c);
		virtual ~EntityInfo();
	private:
		inline void init(const EntityInfo &_c);

	};
}

#endif	/* _ENTITYINFO_H */

