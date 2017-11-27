#include <iomanip>
#include <fstream>
#include <sstream>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/irange.hpp>
#include <boost/filesystem.hpp>
#include <QBitmap>

#include "MapInfo.h"


namespace map_info
{
const char editorVersion[] = "0.0.1";
const char mapFileTopString[] = "Strategix Map";
const char terrainsDefFileName[] = "terrains.def";
const char objectsDefFileName[] = "objects.def";
const char configDir[] = "config/";
const char imagesPath[] = "config/images/";
const char mapConfigPath[] = "config/map/";

umap<string, u_p<TerrainInfo>> MapInfo::terrainInfos;
umap<string, u_p<ToolInfo>> MapInfo::objectInfos;
vector<QPixmap> MapInfo::playerMarks;


MapInfo::MapInfo(const QString& name, int width, int height)
		: name(name), width(width), height(height)
{
	CheckDimentions();
	
	tiles.reserve(height);
	for (int row = 0; row < height; ++row)
	{
		auto& t = tiles.emplace_back();
		t.reserve(width);
		for (int col = 0; col < width; ++col)
		{
			t.push_back({ terrainInfos["none"].get(), nullptr });
		}
	}
}

MapInfo::MapInfo(const QString& fileName)
{
	LoadFromFile(fileName);
}

TerrainInfo* MapInfo::GetTerrainById(int id) noexcept
{
	using namespace boost;
	using namespace boost::adaptors;
	
	auto&& range = terrainInfos | map_values;
	auto it = find_if(range, [id](auto&& info) { return info ? info->id == id : false; });
	return it != range.end() ? it->get() : nullptr;
}

const QPixmap& MapInfo::GetPlayerMark(int playerNumber)
{
	if (playerMarks.empty())
		nya_throw << "Call LoadObjectInfos() first.";
	
	return playerMarks[playerNumber < playerMarks.size() ? playerNumber : 0];
}

void MapInfo::LoadTerrainInfos()
{
	using namespace boost;
	using namespace boost::adaptors;
	using path = boost::filesystem::path;
	
	// definition
	path fileName = path(mapConfigPath) / terrainsDefFileName;
	ifstream fin(fileName.string());
	if (!fin)
	{
		nya_throw << "%s could not be loaded."s % fileName;
	}
	
	std::string terrainsImageFileName;
	getline(fin, terrainsImageFileName);
	
	// image
	QPixmap pixmap;
	if (!pixmap.load((path(mapConfigPath) / terrainsImageFileName).string().c_str()))
	{
		nya_throw << "The image files could not be loaded from " << terrainsImageFileName;
	}
	
	int divs;
	fin >> divs;
	int tileSize = pixmap.width() / divs;
	
	for (int i : irange(0, divs * divs))
	{
		auto info = make_u<TerrainInfo>();
		fin >> info->retard >> info->name;
		if (info->name.empty()) break;
		
		int col = i % divs, row = i / divs;
		info->image = pixmap.copy(col * tileSize, row * tileSize, tileSize, tileSize);
		info->type = ToolType::TERRAIN;
		info->id = i;
		
		terrainInfos.emplace(info->name, std::move(info));
	}
	fin.close();
}

void MapInfo::LoadObjectInfos()
{
	using path = boost::filesystem::path;
	
	path fileName = path(mapConfigPath) / objectsDefFileName;
	ifstream fin(fileName.string());
	if (!fin)
	{
		nya_throw << "%s could not be loaded."s % fileName;
	}
	
	for (;;)
	{
		string type, imageFileName, imageSubdir;
		fin >> type >> imageFileName;
		if (type.empty()) break;
		
		ToolType objectType = type;
		switch (objectType)
		{
			case ToolType::MINE:
				imageSubdir = "mines/";
				break;
			case ToolType::OBJECT:
				imageSubdir = "objects/";
				break;
			default:
				nya_throw << "Cannot handle map object of type: " << type;
		}
		
		string pixmapPath = (path(mapConfigPath) / imageSubdir / imageFileName).string();
		QPixmap pixmap = LoadPixmap(pixmapPath);
		
		auto info = make_u<ToolInfo>();
		info->type = objectType;
		info->name = path(imageFileName).stem().string();
		info->image = pixmap;
		objectInfos.emplace(info->name, move(info));
	}
	fin.close();
	
	// player marks
	string pixmapPath = (path(mapConfigPath) / "player_mark.png").string();
	QPixmap pixmap = LoadPixmap(pixmapPath);
	playerMarks.push_back(pixmap);
	
	QBitmap mask = pixmap.createMaskFromColor(Qt::transparent);
	for (int color = Qt::red; color < Qt::darkRed; ++color)
	{
		QPixmap playerMark(pixmap.size());
		playerMark.fill((Qt::GlobalColor)color);
		playerMark.setMask(mask);
		playerMarks.push_back(playerMark);
	}
}

QPixmap MapInfo::LoadPixmap(const string& path)
{
	QPixmap pixmap;
	if (!pixmap.load(path.c_str()))
	{
		nya_throw << "The image files could not be loaded from " << path;
	}
	return pixmap;
}

void MapInfo::SaveToFile(const QString& fileName) const
{
	ofstream fout(fileName.toStdString());
	if (!fout)
		nya_throw << "Unable to save to " << fileName.toStdString();
	
	stringstream sout;
	
	// top string and version
	sout << mapFileTopString << "\n"
	     << editorVersion << "\n"
	     << "\n";
	
	uset<TerrainInfo*> uniqueTerrains;
	vector<pair<QPoint, PlayerObject*>> objects;
	vector<pair<QPoint, MineObject*>> mines;
	
	// prepare terrain
	stringstream terrainStream;
	for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			auto& tile = tiles[row][col];
			auto terrain = (TerrainInfo*) tile.terrain;
			uniqueTerrains.insert(terrain);
			
			int id = terrain->id;
			terrainStream << setw(2) << id << " ";
			
			if (tile.object)
			{
				if (tile.object->info.type == ToolType::OBJECT)
				{
					objects.emplace_back(QPoint(col, row), (PlayerObject*) tile.object.get());
				}
				else if (tile.object->info.type == ToolType::MINE)
				{
					mines.emplace_back(QPoint(col, row), (MineObject*) tile.object.get());
				}
			}
		}
		terrainStream << "\n";
	}
	terrainStream << "\n";
	
	// terrain descriptions
	sout << uniqueTerrains.size() << "\n";
	for (TerrainInfo* terrain : uniqueTerrains)
	{
		int id = terrain->id;
		string name = terrain->name;
		float retard = terrain->retard;
		sout << id << " " << name << " " << retard << "\n";
	}
	sout << "\n";
	
	// terrain map
	// dimensions
	sout << width << " " << height << "\n"
	     << terrainStream.str();
	
	// objects
	sout << objects.size() << "\n";
	for (auto&& pos_info : objects)
	{
		sout << pos_info.first.x() << " " << pos_info.first.y() << " "
		     << pos_info.second->info.name << " " << pos_info.second->owner << "\n";
	}
	sout << "\n";
	
	// mines
	sout << mines.size() << "\n";
	for (auto&& pos_info : mines)
	{
		sout << pos_info.first.x() << " " << pos_info.first.y() << " "
		     << pos_info.second->info.name << " " << pos_info.second->amount << "\n";
	}
	
	fout << sout.rdbuf();
}

void MapInfo::LoadFromFile(const QString& fileName)
{
	using path = boost::filesystem::path;
	name = path(fileName.toStdString()).filename().string().c_str();
	
	ifstream fin(fileName.toStdString());
	if (!fin)
		nya_throw << "Unable to load from " << fileName.toStdString();
	
	string oneString;
	
	// top string
	getline(fin, oneString);
	if (oneString != mapFileTopString)
		nya_throw << "%s is not a map file."s % fileName.toStdString();
	
	// version
	getline(fin, oneString);
	if (oneString != editorVersion)
		nya_throw << "Version of map [%s] should be [%s]."s % oneString % editorVersion;
	
	// terrain description
	umap<int, string> idName;
	int terrainsNumber;
	fin >> terrainsNumber;
	for (int i = 0; i < terrainsNumber; ++i)
	{
		int id;
		string name;
		float retard;
		fin >> id >> name >> retard;
		
		idName.emplace(id, name);
	}
	
	// dimensions
	fin >> width >> height;
	CheckDimentions();
	
	// map content
	tiles.reserve(height);
	for (int row = 0; row < height; ++row)
	{
		auto& t = tiles.emplace_back();
		t.reserve(width);
		for (int col = 0; col < width; ++col)
		{
			int id;
			fin >> id;
			auto&& terrain = terrainInfos[idName[id]];
			if (!terrain)
			{
				nya_throw << "Terrain with id [%d] is not found"s % id;
			}
			t.push_back({ terrain.get(), nullptr });
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
		
		tiles[row][col].object.reset(new PlayerObject{ *objectInfos[name], owner });
	}
	
	// resources
	fin >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col, amount;
		string name;
		fin >> col >> row >> name >> amount;
		
		tiles[row][col].object.reset(new MineObject{ *objectInfos[name], amount });
	}
	
	if (!fin.good())
		nya_throw << "Map content is corrupted!";
	fin.close();
}

void MapInfo::CheckDimentions()
{
	if (width < 10 || height < 10)
		nya_throw << "Minimum map dimensions (10x10) exceeded: %dx%d"s % width % height;
	if (width > 200 || height > 200)
		nya_throw << "Maximum map dimensions (200x200) exceeded: %dx%d"s % width % height;
}

}