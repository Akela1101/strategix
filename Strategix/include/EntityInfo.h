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
		ResType res; // map<string, SingleResType>
		Params params; // {HP, speed, ...}
		Names depends; // vector<string>
		Names provides; // vector<string>

		string file; // file name with mesh|config|...(put here the file you need)
		float scale; // Scale of mesh|pictures

		// Add here Entity variables, than add some strings in TechTreesBuilder*.Build(),
		// than use it as Kernel::GS().techTrees[race]->techMap[entity]->your_variable

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

