/* 
 * File:   TechTree.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:14
 */

#ifndef _TECHTREE_H
#define	_TECHTREE_H

#include "Nya.hpp"
#include "EntiInfo.h"

#include <map>
#include <string>


namespace Strategix
{
	using namespace std;
	using namespace boost;

	typedef map<string, sh_p<EntiInfo> > TechMapType;
	//typedef std::pair<string, sh_p<EntiInfo> > TechMapPairType;

	class TechTree
	{
	public:
		string raceName;		
		TechMapType techMap;

	public:
		TechTree(const string &raceName);
		TechTree(const TechTree &_c);
		TechTree & operator =(const TechTree &_c);
		inline void init(const TechTree &_c);
		virtual ~TechTree();

		void AddNode(const sh_p<EntiInfo> &shpEntiInfo);

	};

	typedef map<string, sh_p<TechTree> > TechTreesType;
}

#endif	/* _TECHTREE_H */

