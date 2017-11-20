#ifndef BaseMap_H
#define BaseMap_H

#include <strx/common/Strategix_Forward.h>


namespace strx
{
class BaseMap
{
	friend class MapManager;
	using CellsType = vector<vector<Cell>>;
	
	size_t width;
	size_t length;
	CellsType cells; /// [rows][columns] (i.e. [y][x])
	
	BaseMap() = default;
	
public:
	BaseMap(size_t width, size_t length, const CellsType& cells) : width(width), length(length), cells(cells) {}
	BaseMap(const BaseMap& other) : width(other.width), length(other.length), cells(other.cells) {}
	virtual ~BaseMap() {}
	
	size_t GetWidth() const { return width; }
	size_t GetLength() const { return length; }
	Cell& GetCell(int x, int y) { return cells[y][x]; }
	Cell& GetCell(const MapCoord mc) { return cells[mc.y][mc.x]; }
	const Cell& GetCell(int x, int y) const { return cells[y][x]; }
	const Cell& GetCell(const MapCoord mc) const { return cells[mc.y][mc.x]; }
	bool IsCell(const MapCoord& mc) const { return !(mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length); }
};
}

#endif //BaseMap_H
