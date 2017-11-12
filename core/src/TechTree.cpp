#include "EntiInfo.h"
#include "TechTree.h"


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
		techMap[pa.first] = pa.second->clone();
	}
}

void TechTree::AddNode(s_p<EntiInfo> entiInfo)
{
	auto pairEl = make_p(entiInfo->name, entiInfo);
	pair<TechMapType::iterator, bool> retPair = techMap.insert(pairEl);
	if (!retPair.second) STRATEGIX_THROW("More than one EntiInfo with name: " + entiInfo->name);
}

}
