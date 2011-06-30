/* 
 * File:   ResourceInfo.h
 * Author: Akela1101
 *
 * Created on 18 Май 2011 г., 13:18
 */

#ifndef _RESOURCEINFO_H
#define	_RESOURCEINFO_H

#include <map>
#include <string>

#include "Strategix_Forward.h"


namespace Strategix
{
	struct ResourceInfo
	{
		const string name;

		ResourceInfo(const string name)	: name(name) {}
		virtual ~ResourceInfo() {}
	};

	typedef std::map<std::string, sh_p<ResourceInfo> > ResourceInfosType;
}

#endif	/* _RESOURCEINFO_H */

