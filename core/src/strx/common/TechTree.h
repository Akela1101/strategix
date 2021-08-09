#pragma once

#include <Strategix_fwd.h>


namespace strx
{

class TechTree : boost::noncopyable
{
	using TechMapType = umap<string, u_p<EntityInfo>>;

	const string raceName;
	TechMapType techMap;

public:
	TechTree(const string& raceName) : raceName(raceName) {}
	virtual ~TechTree() = default;

	const string& GetRaceName() const { return raceName; }
	const EntityInfo& GetNode(const string& name) const;
	void AddNode(u_p<EntityInfo> entiInfo);
};
}  // namespace strx
