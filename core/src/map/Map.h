#ifndef _MAP_H
#define _MAP_H

#include "common/Strategix_Forward.h"


namespace strategix
{

class Map
{
	friend class MapManager;
	
	size_t width, length;
	vector<vector<Cell>> cells; // [rows][columns] (i.e. [y][x])
	
	Player* player;            // owner
	MapManager* mapManager;    // For pushing synchronizing calls
	u_p<MapsPathsFinder> pathsFinder;

public:
	Map(MapManager* mapFull);
	Map(const Map& _c) = delete;
	Map& operator=(const Map& _c) = delete;
	~Map();
	
	size_t GetWidth() const { return width; }
	size_t GetLength() const { return length; }
	Cell& GetCell(int x, int y) { return cells[y][x]; }
	Cell& GetCell(const MapCoord mc) { return cells[mc.y][mc.x]; }
	const Cell& GetCell(int x, int y) const { return cells[y][x]; }
	const Cell& GetCell(const MapCoord mc) const { return cells[mc.y][mc.x]; }
	bool IsCell(const MapCoord& mc) const { return !(mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length); }
	
	u_p<MapsPath> FindPath(MapCoord from, MapCoord till) const;
	ResourceUnit PickResource(Mine* mine, ResourceUnit amount);
	void RemoveMine(Mine* mine);
};
}

#endif    /* _MAP_H */

