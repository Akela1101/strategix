#ifndef _TECHTREEBUILDER_H
#define    _TECHTREEBUILDER_H

#include "TechTree.h"


namespace strategix
{
class TechTreesBuilder
{
public:
	virtual ~TechTreesBuilder() {};
	
	virtual void Build(TechTreesType* pTechTrees) = 0;
};
}

#endif    /* _TECHTREEBUILDER_H */

