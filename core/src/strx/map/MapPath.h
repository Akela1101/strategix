#ifndef _MAPPATH_H
#define _MAPPATH_H

#include "Strategix_Forward.h"


namespace strx
{
class MapPath
{
	vector<MapCoord> path;

public:
	MapPath() = default;
	MapPath(const MapPath&) = delete;
	MapPath& operator=(const MapPath&) = delete;
	
	bool IsEmpty() { return path.empty(); }
	
	MapCoord TakeNext()
	{
		MapCoord frontCoord = path.back();
		path.pop_back();
		return frontCoord;
	}
	
	void AddPoint(MapCoord mapCoord) { path.push_back(mapCoord); }
};
}

#endif //_MAPPATH_H

