/* 
 * File:   TechTree.cpp
 * Author: Akela1101
 * 
 * Created on 12 Март 2010 г., 18:14
 */

#include "EntiInfo.h"
#include "StrategixError.h"

#include "TechTree.h"


namespace Strategix
{
	using namespace std;
	using namespace boost;


TechTree::TechTree(const string &raceName)
	:
	raceName(raceName)
{}

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
	raceName = _c.raceName;
	mainBuildingName = _c.mainBuildingName;
	
	foreach(const TechMapType::value_type &pa, _c.techMap)
	{
		techMap[pa.first].reset(pa.second->copy());
	}
}

void TechTree::AddNode(sh_p<EntiInfo> entityInfo)
{
	pair<string, sh_p<EntiInfo> > pairEl(entityInfo->name, entityInfo);
	pair<TechMapType::iterator, bool> retPair = techMap.insert(pairEl);
	if( retPair.second == false )
		STRATEGIX_ERROR("More than one EntiInfo with name: " + entityInfo->name);
}

}
