#include "EntiInfo.h"


namespace Strategix
{
using namespace std;


TechTree::TechTree(const string& raceName)
		: raceName(raceName) {}

TechTree::TechTree(const TechTree& _c)
{
	init(_c);
}

TechTree& TechTree::operator=(const TechTree& _c)
{
	if (this != &_c)
	{
		init(_c);
	}
	return *this;
}

void TechTree::init(const TechTree& _c)
{
	raceName = _c.raceName;
	mainBuildingName = _c.mainBuildingName;
	
	for (auto&& pa : _c.techMap)
	{
		techMap[pa.first].reset(pa.second->copy());
	}
}

void TechTree::AddNode(s_p<EntiInfo> entiInfo)
{
	pair<string, s_p<EntiInfo>> pairEl(entiInfo->name, entiInfo);
	pair<TechMapType::iterator, bool> retPair = techMap.insert(pairEl);
	if (!retPair.second) STRATEGIX_EXCEPTION("More than one EntiInfo with name: " + entiInfo->name);
}

}
