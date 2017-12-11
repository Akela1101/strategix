#ifndef _MAPPATHFINDER_H
#define _MAPPATHFINDER_H

#include "Strategix_Forward.h"


namespace strx
{
struct PricedCell;

/**
 * Simple A* implementation.
 */
class MapPathFinder : boost::noncopyable
{
	const Map& map;

public:
	MapPathFinder(const Map& map);
	
	/**
	 * @return non-null path to the point closest to till
	 */
	u_p<MapPath> FindPath(MapCoord from, MapCoord till) const;

private:
	bool IsAccessible(const MapCoord& coord) const;
	u_p<MapPath> GetWay(PricedCell* cell) const;
};
}
#endif //_MAPPATHFINDER_H

