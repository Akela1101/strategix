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
	:
	raceName(raceName)
{
}

void TechTree::AddNode(const sh_p<EntityInfo> &entityInfo)
{
	pair<string, sh_p<EntityInfo> > pairEl(entityInfo->name, entityInfo);
	pair<TechMapType::iterator, bool> retPair = techMap.insert(pairEl);
	if( retPair.second == false )
		throw STRATEGIX_ERROR( string("More than one EntityInfo with name: ") + entityInfo->name );
}
