#ifndef _MAPPATHFINDER_H
#define _MAPPATHFINDER_H

#include "Strategix_Forward.h"


namespace strx
{
/**
 * Simple A* implementation.
 */
class MapPathFinder : boost::noncopyable
{
	const Map& map;

public:
	MapPathFinder(const Map& map);
	
	u_p<MapPath> FindPath(MapCoord from, MapCoord till) const;

private:
	bool IsAccessible(const MapCoord& coord) const;
};
}
#endif //_MAPPATHFINDER_H

