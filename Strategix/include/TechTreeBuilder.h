/* 
 * File:   TechTreeBuilder.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:35
 */

#ifndef _TECHTREEBUILDER_H
#define	_TECHTREEBUILDER_H

#include "TechTree.h"


namespace Strategix
{
	using namespace std;

	class TechTree;

	class TechTreeBuilder // Abstract
	{
	public:
		virtual ~TechTreeBuilder() {};

		virtual void Build(TechTree *p_tech_tree) = 0;
	};
}

#endif	/* _TECHTREEBUILDER_H */

