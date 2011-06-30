/* 
 * File:   MapResource.h
 * Author: Akela1101
 *
 * Created on 18 Май 2011 г., 20:04
 */

#ifndef _MAPRESOURCE_H
#define	_MAPRESOURCE_H

#include "KernelBase.h"

#include <string>

#include "Strategix_Forward.h"


namespace Strategix
{
	using namespace std;
	
	struct MapResource
	{
		const ResourceInfo &resourceInfo;
		const MapCoord mapCoord;
		float amount;

		MapResource(const string name, const MapCoord mapCoord, const float amount)
			: resourceInfo(KernelBase::GS().GetResourceInfo(name)), mapCoord(mapCoord), amount(amount)
		{}
	};
}

#endif	/* _MAPRESOURCE_H */

