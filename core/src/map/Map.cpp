#include <boost/filesystem.hpp>
#include <fstream>
#include <iomanip>
#include <nya/io.hpp>
#include <sstream>

#include "../../strx/MapMine.hpp"
#include "../../strx/MapObject.hpp"

#include "../../strx/Map.hpp"


namespace strx
{
const char mapFileTopString[] = "Strategix Map";
const char mapFormatVersion[] = "0.0.1";


Cell::Cell(Terrain* terrain, MapObject* object) : terrain(terrain), object(object) {}

Cell::Cell(const Cell& other) : terrain(other.terrain), object(other.object ? other.object->clone() : nullptr) {}


Map::Map(string name, int width, int height, TerrainsType terrains)
        : name(move(name)), width(width), length(length), terrains(move(terrains))
{
	CheckDimentions();

	cells.reserve(height);
	for (int row = 0; row < height; ++row)
	{
		auto& t = cells.emplace_back();
		t.reserve(width);
		for (int col = 0; col < width; ++col) { t.emplace_back(this->terrains->at("none").get(), nullptr); }
	}
}

Map::Map(string name, const string& data) : name(move(name)), terrains(new umap<string, u_p<Terrain>>())
{
	LoadFromString(data);
}

Map::Map(const string& path)
        : name(boost::filesystem::path(path).stem().string()), terrains(new umap<string, u_p<Terrain>>())
{
	LoadFromFile(path);
}

Map::Map(const Map& other)
        : name(other.name), width(other.width), length(other.length), terrains(other.terrains), cells(other.cells)
{}

Map::~Map() = default;

bool Map::IsCell(MapCoord coord) const
{
	return !(coord.x < 0 || coord.x >= width || coord.y < 0 || coord.y >= length);
}

void Map::UpdateTerrains(const TerrainsType& newTerrains)
{
	for (const Terrain& newTerrain : *newTerrains | nya::map_values | nya::indirected)
	{
		int id = newTerrain.id;
		string name = newTerrain.name;
		auto i = terrains->find(name);
		if (i == terrains->end())  //
		{
			terrains->emplace(name, make_u<Terrain>(id, name, newTerrain.quality));
		}
		else
		{
			Terrain& terrain = *i->second;
			if (terrain.id != id) nya_throw << "Trying to replace terrain id [%d] with [%d]."s % terrain.id % id;

			terrain.quality = newTerrain.quality;
		}
	}
}

void Map::ChangeTerrain(Cell& cell, const string& terrainName)
{
	auto i = terrains->find(terrainName);
	if (i == terrains->end())
	{
		error_log << "Terrain with name [%s] is not registered."s % terrainName;
		return;
	}
	cell.terrain = i->second.get();
}

void Map::ChangeObject(Cell& cell, u_p<MapObject> object)
{
	if (object && !object->id) object->id = ++lastObjectId;
	cell.object = move(object);
}

string Map::SaveToString() const
{
	ostringstream oss;
	Save(oss);
	return oss.str();
}

void Map::SaveToFile(const string& path) const
{
	ofstream ofs(path);
	if (!ofs) nya_throw << "Unable to save to " << path;

	// prevent exceptions from corrupting the file
	ofs << SaveToString();
}

void Map::LoadFromString(const string& data)
{
	istringstream iss(data);
	try
	{
		Load(iss);
	}
	catch (exception& e)
	{
		nya_throw << "Failed to load map from data.\n\t" << e.what();
	}
}

void Map::LoadFromFile(const string& path)
{
	ifstream ifs(path);
	if (!ifs) nya_throw << "Unable to open map file " << path;

	try
	{
		Load(ifs);
	}
	catch (exception& e)
	{
		nya_throw << "Failed to load map file " << path << "\n\t" << e.what();
	}
	ifs.close();
}

void Map::Save(ostream& os) const
{
	// top string and version
	os << mapFileTopString << "\n"
	   << mapFormatVersion << "\n"
	   << "\n";

	// terrain descriptions
	vector<Terrain*> sortedTerrains;
	sortedTerrains.reserve(terrains->size());
	transform(nya_all(*terrains), back_inserter(sortedTerrains), [](auto& pa) { return pa.second.get(); });
	sort(nya_all(sortedTerrains), [](auto& a, auto& b) { return a->id < b->id; });
	//
	os << terrains->size() << "\n";
	for (const Terrain& terrain : sortedTerrains | nya::indirected)
	{
		os << terrain.id << " " << terrain.name << " " << terrain.quality << "\n";
	}
	os << "\n";

	// dimensions
	os << width << " " << length << "\n";

	// terrain map
	vector<pair<MapCoord, MapEntity*>> objects;
	vector<pair<MapCoord, MapMine*>> mines;
	for (int row = 0; row < length; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			auto& cell = GetCell(col, row);
			auto terrain = cell.terrain;

			os << setw(2) << terrain->id << " ";

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
		os << "\n";
	}
	os << "\n";

	// objects
	os << objects.size() << "\n";
	for (auto&& pos_info : objects)
	{
		os << pos_info.first.x << " " << pos_info.first.y << " " << pos_info.second->name << " "
		   << pos_info.second->ownerSpot << "\n";
	}
	os << "\n";

	// mines
	os << mines.size() << "\n";
	for (auto&& pos_info : mines)
	{
		os << pos_info.first.x << " " << pos_info.first.y << " " << pos_info.second->name << " "
		   << pos_info.second->amount << "\n";
	}
	os.flush();
}

void Map::Load(istream& is)
{
	string oneString;

	// top string
	nya_getline(is, oneString);
	if (oneString != mapFileTopString) nya_throw << "First string should be " << mapFileTopString;

	// version
	nya_getline(is, oneString);
	if (oneString != mapFormatVersion)
		nya_throw << "Version of map [%s] should be [%s]."s % oneString % mapFormatVersion;

	// terrain description
	umap<int, Terrain*> id_terrains;
	int terrainsNumber;
	is >> terrainsNumber;
	for (int i = 0; i < terrainsNumber; ++i)
	{
		int id;
		string name;
		float quality;
		is >> id >> name >> quality;

		auto terrain = make_u<Terrain>(id, name, quality);
		id_terrains.emplace(id, terrain.get());
		terrains->emplace(name, move(terrain));
	}
	if (!is.good()) nya_throw << "terrain description is wrong";

	// dimensions
	is >> width >> length;
	CheckDimentions();

	// map content
	cells.clear();
	cells.reserve(length);
	for (int row = 0; row < length; ++row)
	{
		auto& cell = cells.emplace_back();
		cell.reserve(width);
		for (int col = 0; col < width; ++col)
		{
			int id;
			is >> id;
			if (!nya_in(id, id_terrains)) nya_throw << "Terrain with id [%d] is not found"s % id;

			auto terrain = id_terrains[id];
			cell.emplace_back(terrain, nullptr);
		}
	}

	// objects
	lastObjectId = 0;
	int n;
	is >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col, owner;
		string name;
		is >> col >> row >> name >> owner;

		MapCoord coord(col, row);
		GetCell(col, row).object.reset(new MapEntity{++lastObjectId, name, coord, owner});

		auto iSpot = find(nya_all(playerSpots), owner);
		if (iSpot == playerSpots.end()) playerSpots.push_back(owner);
	}
	if (!is.good()) nya_throw << "map entities are wrong";

	sort(nya_all(playerSpots));

	// resources
	is >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col, amount;
		string name;
		is >> col >> row >> name >> amount;

		MapCoord coord(col, row);
		GetCell(col, row).object.reset(new MapMine{++lastObjectId, name, coord, amount});
	}
	if (!is.good()) nya_throw << "map resource mines are wrong";
}

void Map::CheckDimentions()
{
	if (width < 10 || length < 10) nya_throw << "Minimum map dimensions (10x10) exceeded: %dx%d"s % width % length;
	if (width > 200 || length > 200) nya_throw << "Maximum map dimensions (200x200) exceeded: %dx%d"s % width % length;
}

}  // namespace strx
