#pragma once

#include "Strategix_fwd.h"


namespace strx
{
struct PricedCell;

/**
 * Simple A* implementation.
 */
class PathFinder : boost::noncopyable
{
	const Map& map;

public:
	PathFinder(const Map& map);

	/**
	 * @return non-null path to the point closest to till
	 */
	u_p<MapPath> FindPath(MapCoord from, MapCoord till, float radius = 0) const;

private:
	bool IsAccessible(const MapCoord& coord) const;
	u_p<MapPath> GetWay(PricedCell* cell, bool isFound) const;
};
}  // namespace strx
