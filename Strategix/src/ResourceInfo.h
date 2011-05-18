/* 
 * File:   ResourceInfo.h
 * Author: Akela1101
 *
 * Created on 18 Май 2011 г., 13:18
 */

#ifndef _RESOURCEINFO_H
#define	_RESOURCEINFO_H

namespace Strategix
{
	struct ResourceInfo
	{
		const string name;
		const string meshName;
		const int index; // index in resource vector

		ResourceInfo(const string name, const string meshName, const int index)
			:name(name), meshName(meshName), index(index) {}
	};
}

#endif	/* _RESOURCEINFO_H */

