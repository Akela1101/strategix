#pragma once

#include <Strategix_fwd.h>

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
	using TerrainsType = s_p<umap<string, u_p<Terrain>>>;

private:
	string name;
	int width;
	int length;
	TerrainsType terrains;  /// terrain descriptions
	CellsType cells;        /// [rows][columns] (i.e. [y][x])

public:
	Map(string name, int width, int height, TerrainsType terrains);
	Map(string name, const string& data);
	Map(const string& path);
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
	void UpdateTerrains(const TerrainsType& newTerrains);
	void ChangeTerrain(Cell& cell, const string& terrainName);
	void ChangeObject(Cell& cell, MapObject* object);
	string SaveToString() const;
	void SaveToFile(const string& path) const;

private:
	void LoadFromString(const string& data);
	void LoadFromFile(const string& path);
	void Save(ostream& os) const;
	void Load(istream& is);
	void CheckDimentions();
};
}
