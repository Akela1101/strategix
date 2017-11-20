#ifndef _TECHTREE_H
#define _TECHTREE_H

#include <strx/common/Strategix_Forward.h>


namespace strx
{

class TechTree
{
	using TechMapType = umap<string, u_p<EntiInfo>>;
	
	const string raceName;
	TechMapType techMap;

public:
	TechTree(const string& raceName) : raceName(raceName) {}
	virtual ~TechTree() = default;
	TechTree(const TechTree&) = delete;
	TechTree& operator=(const TechTree&) = delete;
	
	const string& GetRaceName() const { return raceName; }
	const EntiInfo& GetNode(const string& name) const;
	void AddNode(u_p<EntiInfo> entiInfo);
};
}

#endif    /* _TECHTREE_H */

