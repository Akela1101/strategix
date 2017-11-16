#ifndef _MAPSPATH_H
#define    _MAPSPATH_H

#include <deque>

#include "Strategix_Forward.h"


namespace strategix
{
class MapsPath
{
	std::deque<MapCoord> path; // vector ???

public:
	MapsPath() = default;
	
	bool IsEmpty() { return path.empty(); }
	
	MapCoord PickFront()
	{
		MapCoord frontCoord = path.back();
		path.pop_back();
		return frontCoord;
	}
	
	void PushFront(MapCoord mapCoord) { path.push_back(mapCoord); }
	
	MapsPath(const MapsPath& _c) = delete;
	MapsPath& operator=(const MapsPath& _c) = delete;
};
}

#endif    /* _MAPSPATH_H */

