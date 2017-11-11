#ifndef _MAPRESOURCE_H
#define    _MAPRESOURCE_H

#include "KernelBase.h"
#include "Resource.h"

#include "Strategix_Forward.h"


namespace Strategix
{
using namespace std;

class MapResource
{
	friend class MapFull;
	
	Resource resource;

public:
	const MapCoord mapCoord;

public:
	MapResource(Resource resource, MapCoord mapCoord)
			: resource(resource), mapCoord(mapCoord) {}
	
	s_p<const ResourceInfo> GetResourceInfo() const { return KernelBase::GS().GetResourceInfo(resource); }
	
	const Resource& GetResource() const { return resource; }
};
}

#endif    /* _MAPRESOURCE_H */

