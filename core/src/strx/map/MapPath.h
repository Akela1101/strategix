#pragma once

#include "Strategix_Forward.h"


namespace strx
{
class MapPath : boost::noncopyable
{
	bool isWhole;           /// if false, path does not reach the finish point
	vector<MapCoord> path;  /// list of path coordinates without the first one

public:
	MapPath(bool isWhole = true) : isWhole(isWhole) {}
	
	bool IsWhole() const { return isWhole; }
	bool IsEmpty() const { return path.empty(); }
	
	MapCoord TakeNext()
	{
		MapCoord frontCoord = path.back();
		path.pop_back();
		return frontCoord;
	}
	
	void AddPoint(MapCoord mapCoord) { path.push_back(mapCoord); }
};
}
