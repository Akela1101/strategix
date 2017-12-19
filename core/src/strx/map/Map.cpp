#include <iomanip>
#include <fstream>
#include <sstream>

#include <strx/kernel/Kernel.h>
#include <strx/map/MapObject.h>
#include <strx/map/MapMine.h>
#include <strx/player/Player.h>

#include "Map.h"


namespace strx
{
const char mapFileTopString[] = "Strategix Map";
const char mapFormatVersion[] = "0.0.1";

int MapObject::lastId = 0;
umap<string, u_p<Terrain>> Map::terrains;


Map::Cell::Cell(Terrain* terrain, MapObject* object)
		: terrain(terrain)
		, object(object) {}

Map::Cell::Cell(const Map::Cell& other)
		: terrain(other.terrain)
		, object(other.object ? other.object->clone() : nullptr) {}


void Map::AddTerrain(u_p<Terrain> terrain)
{
	terrains.emplace(terrain->name, move(terrain));
}


Map::Map(string name, int width, int height)
		: name(move(name))
		, width(width)
		, length(length)
{
	CheckDimentions();
	
	cells.reserve(height);
	for (int row = 0; row < height; ++row)
	{
		auto& t = cells.emplace_back();
		t.reserve(width);
		for (int col = 0; col < width; ++col)
		{
			t.emplace_back(terrains["none"].get(), nullptr);
		}
	}
}

Map::Map(const string& path, string name)
		: name(move(name))
{
	namespace fs = boost::filesystem;
	if (name.empty()) name = fs::path(path).stem().string();
	
	LoadFromFile(path);
}

Map::Map(const Map& other)
		: name(other.name)
		, width(other.width)
		, length(other.length)
		, cells(other.cells)
{
}

Map::~Map() = default;

bool Map::IsCell(MapCoord coord) const
{
	return !(coord.x < 0 || coord.x >= width || coord.y < 0 || coord.y >= length);
}

void Map::ChangeTerrain(Cell& cell, const string& terrainName)
{
	cell.terrain = terrains[terrainName].get();
}

void Map::ChangeObject(Cell& cell, MapObject* object)
{
	cell.object.reset(object);
}

void Map::SaveToFile(const string& path) const
{
	ofstream fout(path);
	if (!fout)
		nya_throw << "Unable to save to " << path;
	
	stringstream sout;
	
	// top string and version
	sout << mapFileTopString << "\n"
	     << mapFormatVersion << "\n"
	     << "\n";
	
	uset<Terrain*> uniqueTerrains;
	vector<pair<MapCoord, MapEntity*>> objects;
	vector<pair<MapCoord, MapMine*>> mines;
	
	// prepare terrain
	stringstream terrainStream;
	for (int row = 0; row < length; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			auto& cell = GetCell(col, row);
			auto terrain = cell.terrain;
			uniqueTerrains.insert(terrain);
			
			terrainStream << setw(2) << terrain->id << " ";
			
			if (cell.object)
			{
				if (dynamic_cast<MapEntity*>(cell.object.get()))
				{
					objects.emplace_back(MapCoord(col, row), (MapEntity*) cell.object.get());
				}
				else if (dynamic_cast<MapMine*>(cell.object.get()))
				{
					mines.emplace_back(MapCoord(col, row), (MapMine*) cell.object.get());
				}
			}
		}
		terrainStream << "\n";
	}
	terrainStream << "\n";
	
	// terrain descriptions
	sout << uniqueTerrains.size() << "\n";
	for (Terrain* terrain : uniqueTerrains)
	{
		sout << terrain->id << " " << terrain->name << "\n";
	}
	sout << "\n";
	
	// terrain map
	// dimensions
	sout << width << " " << length << "\n"
	     << terrainStream.str();
	
	// objects
	sout << objects.size() << "\n";
	for (auto&& pos_info : objects)
	{
		sout << pos_info.first.x << " " << pos_info.first.y << " "
		     << pos_info.second->name << " " << pos_info.second->owner << "\n";
	}
	sout << "\n";
	
	// mines
	sout << mines.size() << "\n";
	for (auto&& pos_info : mines)
	{
		sout << pos_info.first.x << " " << pos_info.first.y << " "
		     << pos_info.second->name << " " << pos_info.second->amount << "\n";
	}
	
	fout << sout.rdbuf();
}

void Map::LoadFromFile(const string& path)
{
	ifstream fin(path);
	if (!fin)
		nya_throw << "Unable to open map file " << path;
	
	string oneString;
	
	// top string
	getline(fin, oneString);
	if (oneString != mapFileTopString)
		nya_throw << "%s is not a map file."s % path;
	
	// version
	getline(fin, oneString);
	if (oneString != mapFormatVersion)
		nya_throw << "Version of map [%s] should be [%s]."s % oneString % mapFormatVersion;
	
	// terrain description
	umap<int, Terrain*> id_terrains;
	int terrainsNumber;
	fin >> terrainsNumber;
	for (int i = 0; i < terrainsNumber; ++i)
	{
		int id;
		string name;
		fin >> id >> name;
		
		auto terrain = terrains[name].get();
		if (!terrain) nya_throw << "Terrain with name %s is not found"s % name;
		
		id_terrains.emplace(id, terrain);
	}
	if (!fin.good()) nya_throw << "terrain description is wrong";
	
	// dimensions
	fin >> width >> length;
	CheckDimentions();
	
	// map content
	cells.reserve(length);
	for (int row = 0; row < length; ++row)
	{
		auto& cell = cells.emplace_back();
		cell.reserve(width);
		for (int col = 0; col < width; ++col)
		{
			int id;
			fin >> id;
			if (!in_(id, id_terrains))
			{
				nya_throw << "Terrain with id [%d] is not found"s % id;
			}
			auto terrain = id_terrains[id];
			cell.emplace_back(terrain, nullptr);
		}
	}
	
	// objects
	int n;
	fin >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col, owner;
		string name;
		fin >> col >> row >> name >> owner;
		
		MapCoord coord(col, row);
		GetCell(col, row).object.reset(new MapEntity{ name, coord, owner });
	}
	if (!fin.good()) nya_throw << "map entities are wrong";
	
	// resources
	fin >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col, amount;
		string name;
		fin >> col >> row >> name >> amount;
		
		MapCoord coord(col, row);
		GetCell(col, row).object.reset(new MapMine{ name, coord, amount });
	}
	if (!fin.good()) nya_throw << "map resource mines are wrong";
	
	fin.close();
}

void Map::CheckDimentions()
{
	if (width < 10 || length < 10)
		nya_throw << "Minimum map dimensions (10x10) exceeded: %dx%d"s % width % length;
	if (width > 200 || length > 200)
		nya_throw << "Maximum map dimensions (200x200) exceeded: %dx%d"s % width % length;
}

}