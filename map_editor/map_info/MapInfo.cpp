#include <iomanip>
#include <fstream>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <QFileInfo>
#include <QMessageBox>

#include "MapInfo.h"


namespace map_info
{
const char editorTitle[] = "Strategix Map Editor";
const char editorVersion[] = "0.0.1";
const char mapFileTopString[] = "Strategix Map";
const char terrainsDefinitionFileName[] = "terrains.def";
const char configDir[] = "config/";
const char imagesPath[] = "config/images/";

umap<std::string, u_p<TerrainInfo>> MapInfo::terrainInfos;
umap<ToolType, u_p<ToolInfo>> MapInfo::objectInfos;


MapInfo::MapInfo(const QString& name, int width, int height)
		: name(name), width(width), height(height)
{
	try
	{
		CheckDimentions();
		
		tiles.reserve(height);
		for (int row = 0; row < height; ++row)
		{
			auto& t = tiles.emplace_back();
			t.reserve(width);
			for (int col = 0; col < width; ++col)
			{
				t.push_back({ terrainInfos["grass1"].get(), nullptr });
			}
		}
	}
	catch (exception& e)
	{
		QMessageBox::critical(nullptr, QString("Error creating map: %1").arg(name), e.what());
	}
}

MapInfo::MapInfo(const QString& fileName)
{
	try
	{
		LoadFromFile(fileName);
	}
	catch (exception& e)
	{
		QMessageBox::critical(nullptr, QString("Error while reading the file: %1").arg(fileName), e.what());
	}
}

TerrainInfo* MapInfo::GetTerrainById(int id)
{
	using namespace boost;
	using namespace boost::adaptors;
	return find_if(terrainInfos | map_values, [id](auto&& info) { return info->id == id; })->get();
}

bool MapInfo::SaveToFile(const QString& fileName) const
{
	ofstream fout(fileName.toLocal8Bit());
	
	// Top string and version
	fout << mapFileTopString << "\n"
	     << editorVersion << "\n"
	     << "\n";
	
	// Dimensions
	fout << width << " " << height << "\n";
	
	vector <QPoint> playerPositions;
	vector <QPoint> objectPositions;
	
	// Terrain
	uset<TerrainInfo*> uniqueTerrains;
	for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			auto& tile = tiles[row][col];
			auto terrain = (TerrainInfo*) tile.terrain;
			uniqueTerrains.insert(terrain);
			
			int id = terrain->id;
			fout << setw(2) << id << " ";
			
			if (tile.object)
			{
				if (tile.object->type == ToolType::PLAYER)
					playerPositions.emplace_back(col, row);
				else
					objectPositions.emplace_back(col, row);
			}
		}
		fout << "\n";
	}
	fout << "\n";
	
	// Terrain descriptions
	fout << uniqueTerrains.size() << "\n";
	for (TerrainInfo* terrain : uniqueTerrains)
	{
		int id = terrain->id;
		string name = terrain->name;
		float retard = terrain->retard;
		fout << id << " " << name << " " << retard << "\n";
	}
	fout << "\n";
	
	// Player initial positions
	fout << playerPositions.size() << "\n";
	for (auto&& pos : playerPositions)
	{
		fout << pos.x() << " " << pos.y() << "\n";
	}
	fout << "\n";
	
	// Mines
	fout << objectPositions.size() << "\n";
	for (auto&& pos : objectPositions)
	{
		fout << pos.x() << " " << pos.y() << " " << "gold" << " " << 100000 << "\n";
	}
	
	fout.close();
	return true;
}

void MapInfo::LoadFromFile(const QString& fileName)
{
	name = QFileInfo(fileName).completeBaseName();
	
	ifstream fin(fileName.toLocal8Bit());
	string oneString;
	
	// Top string
	getline(fin, oneString);
	if (oneString != mapFileTopString)
		throw_nya << "%s is not a map file."s % fileName.toStdString();
	
	// Version
	getline(fin, oneString);
	if (oneString != editorVersion)
		throw_nya << "Version of map [%s] should be [%s]."s % oneString % editorVersion;
	
	// Dimensions
	fin >> width >> height;
	CheckDimentions();
	
	// Map content
	tiles.reserve(height);
	for (int row = 0; row < height; ++row)
	{
		auto& t = tiles.emplace_back();
		t.reserve(width);
		for (int col = 0; col < width; ++col)
		{
			int id;
			fin >> id;
			t.push_back({ GetTerrainById(id), nullptr });
		}
	}
	
	// Terrain description
	int terrainsNumber;
	fin >> terrainsNumber;
	for (int i = 0; i < terrainsNumber; ++i)
	{
		int id;
		string terrainName;
		float retard;
		fin >> id >> terrainName >> retard;
	}
	
	// Player initial positions
	int n;
	fin >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col;
		fin >> col >> row;
		tiles[row][col].object = objectInfos[ToolType::PLAYER].get();
	}
	
	// Resources
	fin >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col, amount;
		string name;
		fin >> col >> row >> name >> amount;
		tiles[row][col].object = objectInfos[ToolType::MINE].get();
	}
	
	if (!fin.good())
		throw_nya << "Map content is corrupted!";
	fin.close();
}

void MapInfo::CheckDimentions()
{
	if (width < 10 || height < 10)
		throw_nya << "Minimum map dimensions (10x10) exceeded: %dx%d"s % width % height;
	if (width > 200 || height > 200)
		throw_nya << "Maximum map dimensions (200x200) exceeded: %dx%d"s % width % height;
}

}