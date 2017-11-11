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

using ResourceInfosType = std::map<std::string, s_p<ResourceInfo>>;
}

#endif    /* _RESOURCEINFO_H */

