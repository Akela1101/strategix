/* 
 * File:   TechTreeBuilderFromXml.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:37
 */

#ifndef _TECHTREEBUILDERFROMXML_H
#define	_TECHTREEBUILDERFROMXML_H

#include "TechTreeBuilder.h"
#include <boost/property_tree/ptree.hpp>

namespace Strategix
{
	using namespace std;
	using namespace boost::property_tree;

	class TechTreeBuilderFromXml : public TechTreeBuilder
	{
		TechTree *p_tech_tree; // Link to building tree

	public:
		virtual void Build(TechTree *p_tech_tree);

	private:
		void BuildEntity(const ptree &entity_pt);
	};
}

#endif	/* _TECHTREEBUILDERFROMXML_H */

