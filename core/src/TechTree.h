#ifndef _TECHTREE_H
#define    _TECHTREE_H

#include <map>
#include <string>

#include "Strategix_Forward.h"


namespace strategix
{
using namespace std;

class TechTree
{
	using TechMapType = map<string, u_p<EntiInfo>>;
	
	const string raceName;
	TechMapType techMap;

public:
	TechTree(const string& raceName) : raceName(raceName) {}
	virtual ~TechTree() = default;
	TechTree(const TechTree& _c) = delete;
	TechTree& operator=(const TechTree& _c) = delete;
	
	const string& GetRaceName() const { return raceName; }
	const EntiInfo& GetNode(const string& name) const;
	void AddNode(u_p<EntiInfo> entiInfo);
};
}

#endif    /* _TECHTREE_H */

