#ifndef _MINE_H
#define    _MINE_H

#include "Kernel.h"
#include "Resource.h"
#include "Strategix_Forward.h"


namespace strategix
{
using namespace std;

class Mine
{
	friend class MapFull;
	
	u_p<Resource> resource;
	const MapCoord mapCoord;

public:
	Mine(u_p<Resource> resource, const MapCoord& mapCoord)
			: resource(move(resource)), mapCoord(mapCoord) {}
	
	const string& GetResourceName() const { return resource->GetName(); }
	const Resource& GetResource() const { return *resource; }
	MapCoord GetCoord() const { return mapCoord; }
};
}

#endif    /* _MINE_H */

