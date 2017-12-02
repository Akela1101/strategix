#ifndef _MINE_H
#define    _MINE_H

#include "strx/kernel/Kernel.h"
#include "strx/common/Resource.h"
#include "Strategix_Forward.h"


namespace strx
{
class Mine
{
	friend class MapManager;
	
	u_p<Resource> resource;
	const MapCoord mapCoord;

public:
	Mine(u_p<Resource> resource, const MapCoord& mapCoord)
			: resource(move(resource)), mapCoord(mapCoord) {}
	
	const string& GetResourceName() const { return resource->GetName(); }
	const Resource& GetResource() const { return *resource; }
	MapCoord GetCoord() const { return mapCoord; }
	
	ResourceUnit PickResource(ResourceUnit amount);
};
}

#endif    /* _MINE_H */

