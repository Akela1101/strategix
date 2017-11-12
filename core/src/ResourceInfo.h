#ifndef _RESOURCEINFO_H
#define    _RESOURCEINFO_H

#include <map>
#include <string>
#include <utility>

#include <Strategix_Forward.h>


namespace Strategix
{
struct ResourceInfo
{
	const string name;
	
	ResourceInfo(string name) : name(std::move(name)) {}
	
	virtual ~ResourceInfo() = default;
};
}

#endif    /* _RESOURCEINFO_H */

