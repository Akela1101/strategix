#ifndef _MAP_H
#define _MAP_H

#include <Strategix_Forward.h>

namespace strx
{
extern const char mapFormatVersion[];

struct Terrain
{
	int id;
	string name;
	float quality;
	
	Terrain(int id, string name, float quality) : id(id), name(move(name)), quality(quality) {}
};

class Map
{
public:
	struct Cell
	{
		Terrain* terrain;
		u_p<MapObject> object;  // can be null
		
		Cell() = default;
		Cell(Terrain* terrain, MapObject* object);
		Cell(const Cell& other);
	};
	using CellsType = vector<vector<Cell>>;

private:
	static umap<string, u_p<Terrain>> terrains;  /// all terrain types
	
	string name;
	int width;
	int length;
	CellsType cells; /// [rows][columns] (i.e. [y][x])
	
public:
	static void AddTerrain(u_p<Terrain> terrain);
	
	Map(string name, int width, int height);
	Map(const string& path, string name = "");
	Map(const Map& other);
	virtual ~Map();
	
	const string& GetName() const { return name; }
	int GetWidth() const { return width; }
	int GetLength() const { return length; }
	Cell& GetCell(int x, int y) { return cells[y][x]; }
	Cell& GetCell(MapCoord coord) { return cells[coord.y][coord.x]; }
	const Cell& GetCell(int x, int y) const { return cells[y][x]; }
	const Cell& GetCell(MapCoord coord) const { return cells[coord.y][coord.x]; }
	
	bool IsCell(MapCoord coord) const;
	void ChangeTerrain(Cell& cell, const string& terrainName);
	void ChangeObject(Cell& cell, MapObject* object);
	void SaveToFile(const string& path) const;

private:
	void LoadFromFile(const string& path);
	void CheckDimentions();
};
}

#endif //_MAP_H
