#ifndef _MAP_H
#define    _MAP_H

#include "Mine.h"

#include <vector>

#include "Strategix_Forward.h"


namespace strategix
{
using namespace std;

class Map
{
public:
	struct Cell
	{
		int terrainType;
		float retard; // defines from terrain type
		mutable s_p<Mine> mine;
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
	
	const Cell& GetCell(int x, int y) const { return cells[y][x]; }
	
	const Cell& GetCell(const MapCoord mc) const { return cells[mc.y][mc.x]; }
	
	virtual float PickResource(Mine* mine, float amount) = 0;
	
	bool IsCell(const MapCoord& mc) const
	{
		return !(mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length);
	}
};
}

#endif    /* _MAP_H */

