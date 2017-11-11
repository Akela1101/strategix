#ifndef _MAPRESOURCE_H
#define    _MAPRESOURCE_H

#include "Kernel.h"
#include "Resource.h"
#include "Strategix_Forward.h"


namespace Strategix
{
using namespace std;

class MapResource
{
	friend class MapFull;
	
	u_p<Resource> resource;
	const MapCoord mapCoord;

public:
	MapResource(u_p<Resource> resource, const MapCoord& mapCoord)
			: resource(move(resource)), mapCoord(mapCoord) {}
	
	const ResourceInfo* GetResourceInfo() const { return Kernel::GetResourceInfo(*resource); }
	
	const Resource& GetResource() const { return *resource; }
	
	MapCoord GetCoord() const { return mapCoord; }
};
}

#endif    /* _MAPRESOURCE_H */

