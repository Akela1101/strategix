/* 
 * File:   TechTree.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:14
 */

#ifndef _TECHTREE_H
#define	_TECHTREE_H

#include <map>
#include <string>

#include "Strategix_Forward.h"


namespace Strategix
{
	using namespace std;
	using namespace boost;

	class TechTree
	{
	public:
		string raceName;
		string mainBuildingName;

	private:
		typedef map<string, sh_p<EntiInfo> > TechMapType;
		TechMapType techMap;

	public:
		TechTree(const string &raceName);
		virtual ~TechTree() {}
		
		TechTree(const TechTree &_c);
		TechTree & operator =(const TechTree &_c);
		inline void init(const TechTree &_c);
		// Don't forget updating copy constuctor after changing member list!

		void AddNode(sh_p<EntiInfo> entiInfo);
		sh_p<EntiInfo> Node(const string name) const
		{
			TechMapType::const_iterator itEi = techMap.find(name);
			if( itEi == techMap.end() )
				STRATEGIX_ERROR("Wrong Enti name: " + name);
			return itEi->second;
		}
	};

	typedef map<string, sh_p<TechTree> > TechTreesType;
}

#endif	/* _TECHTREE_H */

