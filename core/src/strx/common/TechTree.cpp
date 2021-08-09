#include <strx/common/EntityInfo.h>

#include "TechTree.h"


namespace strx
{


const EntityInfo& TechTree::GetNode(const string& name) const
{
	auto it = techMap.find(name);
	if (it == techMap.end()) nya_throw << "Wrong entity name: " << name;

	return *it->second;
}

void TechTree::AddNode(u_p<EntityInfo> entiInfo)
{
	auto iter_ok = techMap.emplace(entiInfo->name, move(entiInfo));
	if (!iter_ok.second) nya_throw << "More than one EntityInfo with name: " << entiInfo->name;
}

}  // namespace strx
