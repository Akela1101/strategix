/* 
 * File:   TechTreesBuilderFromXml.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:37
 */

#ifndef _TECHTREEBUILDERFROMXML_H
#define	_TECHTREEBUILDERFROMXML_H

#include <TechTreesBuilder.h>

#include <boost/property_tree/ptree.hpp>


namespace Sample1
{
	using namespace Strategix;
	using namespace std;
	namespace pt = boost::property_tree;

	class TechTreesBuilderFromXml : public TechTreesBuilder
	{
		TechTreesType *pTechTrees; // Link to building tree

	public:
		virtual void Build(TechTreesType *pTechTrees);

	private:
		void BuildRace(const string &raceName, const pt::ptree &property_tree);
		void BuildEntity(sh_p<TechTree> techTree, const pt::ptree &entity_pt);
	};
}

#endif	/* _TECHTREEBUILDERFROMXML_H */

