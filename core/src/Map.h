#ifndef _MAP_H
#define    _MAP_H

#include "MapResource.h"

#include <vector>

#include "Strategix_Forward.h"


namespace Strategix
{
using namespace std;

class Map
{
public:
	struct Cell
	{
		int terrainType;
		float retard; // defines from terrain type
		mutable s_p<MapResource> mapResource;
		//mutable list<Enti*> entis;
	};

protected:
	string name;
	size_t width, length;
	vector<vector<Cell>> cells; // [rows][columns] (i.e. [y][x])

public:
	virtual ~Map() = default;
	
	const string& GetName() const { return name; }
	
	const size_t GetWidth() const { return width; }
	
	const size_t GetLength() const { return length; }
	
	const Cell& GetCell(const int x, const int y) const { return cells[y][x]; }
	
	const Cell& GetCell(const MapCoord mc) const { return cells[mc.y][mc.x]; }
	
	virtual float PickResource(s_p<MapResource> mapResource, float amount) = 0;
	
	bool IsCell(const MapCoord& mc) const
	{
		return !(mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length);
	}
};
}

#endif    /* _MAP_H */

