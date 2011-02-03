/* 
 * File:   EntiInfo.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:34
 */

#ifndef _ENTIINFO_H
#define	_ENTIINFO_H

#include <map>
#include <string>

#include "GameStructs.h"

namespace Strategix
{
	using namespace std;

	class EntiInfo
	{
	public:
		string name;
		string kind;
		map<string, ResType> resources;
		Params params; // {HP, ...}
		Names depends; // vector<string>
		Names provides; // vector<string>

		string file; // file name with mesh|config|...(put here the file you need)
		float scale; // Scale of mesh|pictures
		map<string, Action> actions;

		// Add here Entity variables, than add some strings in TechTreesBuilder*.Build(),
		// than use it as Kernel::GS().techTrees[race]->techMap[entity]->your_variable

	public:
		EntiInfo();
		virtual ~EntiInfo();

	private:
		EntiInfo(const EntiInfo &_c);
		EntiInfo & operator =(const EntiInfo &_c);
	};
}

#endif	/* _ENTIINFO_H */

