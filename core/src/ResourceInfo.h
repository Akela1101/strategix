/* 
 * File:   ResourceInfo.h
 * Author: Akela1101
 *
 * Created on 18 Май 2011 г., 13:18
 */

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

