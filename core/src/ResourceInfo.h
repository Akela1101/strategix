#ifndef _RESOURCEINFO_H
#define    _RESOURCEINFO_H

#include <map>
#include <string>

#include "Strategix_Forward.h"


namespace Strategix
{
struct ResourceInfo
{
	const string name;
	
	ResourceInfo(string name) : name(name) {}
	
	virtual ~ResourceInfo() = default;
};

typedef std::map<std::string, s_p<ResourceInfo>> ResourceInfosType;
}

#endif    /* _RESOURCEINFO_H */

