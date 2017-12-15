#ifndef _MAP_H
#define _MAP_H

#include <Strategix_Forward.h>

namespace strx
{
extern const char mapFormatVersion[];

class Map
{
public:
	struct Terrain
	{
		int id;
		string name;
		float quality;
		
		Terrain(int id, string name, float quality) : id(id), name(move(name)), quality(quality) {}
	};
	
	struct Cell
	{
		Terrain* terrain;
		u_p<MapObject> object;  // can be null
		
		Cell() = default;
		Cell(Terrain* terrain, MapObject* object);
		Cell(const Cell& other);
	};

protected:
	static umap<string, u_p<Terrain>> terrains;  /// all terrain types
	
private:
	using CellsType = vector<vector<Cell>>;
	
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
	Cell& GetCell(const MapCoord mc) { return cells[mc.y][mc.x]; }
	const Cell& GetCell(int x, int y) const { return cells[y][x]; }
	const Cell& GetCell(const MapCoord mc) const { return cells[mc.y][mc.x]; }
	bool IsCell(const MapCoord& mc) const { return !(mc.x < 0 || mc.x >= width || mc.y < 0 || mc.y >= length); }
	
	u_p<MapPath> FindPath(MapCoord from, MapCoord till, float radius) const;
	ResourceUnit PickResource(MapMine* mine, ResourceUnit amount);
	
	void ChangeTerrain(Cell& cell, const string& terrainName);
	void ChangeObject(Cell& cell, MapObject* object);
	void SaveToFile(const string& path) const;

private:
	void LoadFromFile(const string& path);
	void CheckDimentions();
};
}

#endif //_MAP_H
