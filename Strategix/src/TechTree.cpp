/* 
 * File:   TechTree.cpp
 * Author: Akela1101
 * 
 * Created on 12 Март 2010 г., 18:14
 */

#include "TechTree.h"
#include "Exception.h"

using namespace std;
using namespace boost;
using namespace Strategix;

TechTree::TechTree(const string &raceName)
{
	this->raceName = raceName;
}

const string &TechTree::GetRaceName() const
{
	return raceName;
}

void TechTree::Build(TechTreeBuilder &ttBuilder)
{
	ttBuilder.Build(this);
}

void TechTree::AddNode(const shared_ptr<EntityInfo> &shpEntityInfo)
{
	pair<string, shared_ptr<EntityInfo> > pairEl(shpEntityInfo->name, shpEntityInfo);
	pair<TechMapType::iterator, bool> retPair = techMap.insert(pairEl);
	if( retPair.second == false )
		throw STRAX_ERROR("There is at least 2 entities with the same name.");
}
