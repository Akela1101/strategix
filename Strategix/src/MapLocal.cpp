/* 
 * File:   MapLocal.cpp
 * Author: Akela1101
 * 
 * Created on 24 Март 2011 г., 14:02
 */

#include "MapFull.h"
#include "MapsPathsFinder.h"

#include "MapLocal.h"

namespace Strategix
{

MapLocal::MapLocal(MapFull *mapFull)
	:
	Map(*static_cast<Map*>(mapFull)),
	mapFull(mapFull),
	pathsFinder(new MapsPathsFinder(*this))
{
}

MapLocal::~MapLocal()
{
}

sh_p<MapsPath> MapLocal::FindPath(const MapCoord from, const MapCoord till)
{
	return pathsFinder->FindPath(from, till);
}

}
