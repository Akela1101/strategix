/* 
 * File:   TechTree.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:14
 */

#ifndef _TECHTREE_H
#define	_TECHTREE_H

#include "StrategixError.h"

#include <map>
#include <string>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;
	using namespace boost;

	class EntiInfo;

	class TechTree
	{
	public: // Don't forget updating copy constuctor after changing member list!
		string raceName;
		string mainBuildingName;

	private:
		typedef map<string, sh_p<EntiInfo> > TechMapType;
		TechMapType techMap;

	public:
		TechTree(const string &raceName);
		TechTree(const TechTree &_c);
		TechTree & operator =(const TechTree &_c);
		inline void init(const TechTree &_c);

		sh_p<EntiInfo> Node(const string name) const
		{
			TechMapType::const_iterator itEi = techMap.find(name);
			if( itEi == techMap.end() )
				STRATEGIX_ERROR(string("Wrong Enti name: ") + name);
			return itEi->second;
		}
		void AddNode(sh_p<EntiInfo> entityInfo);

	};

	typedef map<string, sh_p<TechTree> > TechTreesType;
}

#endif	/* _TECHTREE_H */

