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
		float retard;
		
		Terrain(int id, string name, float retard) : id(id), name(move(name)), retard(retard) {}
	};
	
	struct Object
	{
		string name;
		MapCoord coord;
		
		Object(string name, MapCoord coord) : name(move(name)), coord(coord) {}
		Object(const Object& other) : name(other.name), coord(other.coord) {}
		virtual ~Object() {}
		
		virtual Object* clone() = 0;
	};
	struct PlayerObject : Object
	{
		int owner;        // owner player id
		
		PlayerObject(string name, MapCoord coord, int owner) : Object(move(name), coord), owner(owner) {}
		PlayerObject(const PlayerObject& other) : Object(other), owner(other.owner) {}
		Object* clone() override { return new PlayerObject(*this); }
	};
	struct MineObject : Object
	{
		int amount;       // resource amount
		
		MineObject(string name, MapCoord coord, int amount) : Object(move(name), coord), amount(amount) {}
		MineObject(const MineObject& other) : Object(other), amount(other.amount) {}
		Object* clone() override { return new MineObject(*this); }
	};
	
	struct Cell
	{
		Terrain* terrain;
		u_p<Object> object;  // can be null
		
		Cell() = default;
		Cell(Terrain* terrain, Object* object) : terrain(terrain), object(object) {}
		Cell(const Cell& other) : terrain(other.terrain), object(other.object ? other.object->clone() : nullptr) {}
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
	
	u_p<MapsPath> FindPath(MapCoord from, MapCoord till) const;
	ResourceUnit PickResource(Mine* mine, ResourceUnit amount);
	
	void ChangeTerrain(Cell& cell, const string& terrainName);
	void ChangeObject(Cell& cell, Object* object);
	void SaveToFile(const string& path) const;

private:
	void LoadFromFile(const string& path);
	void CheckDimentions();
};
}

#endif //_MAP_H
