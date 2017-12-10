#ifndef _TECHTREE_H
#define _TECHTREE_H

#include <Strategix_Forward.h>


namespace strx
{

class TechTree : boost::noncopyable
{
	using TechMapType = umap<string, u_p<EntiInfo>>;
	
	const string raceName;
	TechMapType techMap;

public:
	TechTree(const string& raceName) : raceName(raceName) {}
	virtual ~TechTree() = default;
	
	const string& GetRaceName() const { return raceName; }
	const EntiInfo& GetNode(const string& name) const;
	void AddNode(u_p<EntiInfo> entiInfo);
};
}

#endif    /* _TECHTREE_H */

