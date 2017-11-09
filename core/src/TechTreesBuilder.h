/* 
 * File:   TechTreesBuilder.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:35
 */

#ifndef _TECHTREEBUILDER_H
#define    _TECHTREEBUILDER_H

#include "TechTree.h"


namespace Strategix
{
class TechTreesBuilder
{
public:
	virtual ~TechTreesBuilder() {};
	
	virtual void Build(TechTreesType* pTechTrees) = 0;
};
}

#endif    /* _TECHTREEBUILDER_H */

