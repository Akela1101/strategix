/* 
 * File:   TechTree.cpp
 * Author: Akela1101
 * 
 * Created on 12 Март 2010 г., 18:14
 */

#include "EntiInfo.h"
#include "Exception.h"

#include "TechTree.h"

using namespace std;
using namespace boost;
using namespace Strategix;


TechTree::TechTree(const string &raceName)
	:
	raceName(raceName)
{
}

TechTree::TechTree(const TechTree &_c)
{
	init(_c);
}

TechTree &TechTree::operator =(const TechTree &_c)
{
	if( this != &_c )
	{
		init(_c);
	}
	return *this;
}

void TechTree::init(const TechTree &_c)
{
	this->raceName = raceName;
	foreach(const TechMapType::value_type &pa, _c.techMap)
	{
		this->techMap[pa.first] = sh_p<EntiInfo>(new EntiInfo(*pa.second));
	}
}

TechTree::~TechTree()
{
}

void TechTree::AddNode(const sh_p<EntiInfo> &entityInfo)
{
	pair<string, sh_p<EntiInfo> > pairEl(entityInfo->name, entityInfo);
	pair<TechMapType::iterator, bool> retPair = techMap.insert(pairEl);
	if( retPair.second == false )
		STRATEGIX_ERROR( string("More than one EntiInfo with name: ") + entityInfo->name );
}
