#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <strx/kernel/Kernel.h>
#include <strx/map/MapObject.h>
#include <strx/map/MapsPath.h>
#include <strx/map/MapsPathsFinder.h>
#include <strx/map/Mine.h>
#include <strx/player/Player.h>

#include "Map.h"


namespace strx
{
const char mapFileTopString[] = "Strategix Map";
const char mapFormatVersion[] = "0.0.1";

umap<string, u_p<Map::Terrain>> Map::terrains;


Map::Cell::Cell(Map::Terrain* terrain, MapObject* object)
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

u_p<MapsPath> Map::FindPath(MapCoord from, MapCoord till) const
{
	MapsPathsFinder pathsFinder(*this);
	return pathsFinder.FindPath(from, till);
}

ResourceUnit Map::PickResource(Mine* mine, ResourceUnit amount)
{
	return mine->PickResource(amount);
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
	vector<pair<MapCoord, PlayerObject*>> objects;
	vector<pair<MapCoord, MineObject*>> mines;
	
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
				if (dynamic_cast<PlayerObject*>(cell.object.get()))
				{
					objects.emplace_back(MapCoord(col, row), (PlayerObject*) cell.object.get());
				}
				else if (dynamic_cast<MineObject*>(cell.object.get()))
				{
					mines.emplace_back(MapCoord(col, row), (MineObject*) cell.object.get());
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
		
		MapCoord coord(row, col);
		GetCell(col, row).object.reset(new PlayerObject{ name, coord, owner });
	}
	if (!fin.good()) nya_throw << "map objects are wrong";
	
	// resources
	fin >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col, amount;
		string name;
		fin >> col >> row >> name >> amount;
		
		MapCoord coord(row, col);
		GetCell(col, row).object.reset(new MineObject{ name, coord, amount });
	}
	if (!fin.good()) nya_throw << "map resources are wrong";
	
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