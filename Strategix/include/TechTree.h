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
#include "boost/smart_ptr.hpp"

#include "EntityInfo.h"
#include "TechTreeBuilder.h"


namespace Strategix
{
	using namespace boost;

	class TechTreeBuilder;

	class TechTree
	{
	public:
		string raceName;
		typedef map<string, shared_ptr<EntityInfo> > TechMapType;
		TechMapType techMap;

	public:
		TechTree(const string &raceName);

		const string &GetRaceName() const;
		void Build(TechTreeBuilder &ttBuilder);
		void AddNode(const shared_ptr<EntityInfo> &shpEntityInfo);

	private:
		TechTree(const TechTree &_c);
		TechTree & operator =(const TechTree &_c);
		inline void init(const TechTree &_c);

	};
}

#endif	/* _TECHTREE_H */

