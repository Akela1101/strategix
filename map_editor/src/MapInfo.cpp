#include "MapInfo.h"

#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <QFileInfo>
#include <QMessageBox>


using namespace std;


const char mapFileTopString[] = "Strategix Map";
const char editorVersion[] = "0.0.1";

QHash<int, s_p<ObjectInfo>> MapInfo::terrInfos;
QHash<int, s_p<ObjectInfo>> MapInfo::objInfos;


MapInfo::MapInfo(const QString& name, size_t width, size_t height)
		: name(name), width(width), height(height)
{
	tiles.reserve(height);
	for (int row = 0; row < height; ++row)
	{
		tiles.push_back(QList<Tile>());
		auto& t = tiles.back();
		t.reserve(width);
		for (int col = 0; col < width; ++col)
		{
			t.push_back({terrInfos[10], nullptr});
		}
	}
}

MapInfo::MapInfo(const QString& fileName)
{
	if (!LoadFromFile(fileName)) //TODO: use exception to get message
	{
		QMessageBox::critical(nullptr, "Unable to open file!", "May be wrong file format or version...");
	}
}

bool MapInfo::SaveToFile(const QString& fileName, const QList<TerrainInfo>& terrainInfos) const
{
	using namespace std;
	ofstream fout(fileName.toLocal8Bit());
	
	// Top string and version
	fout << mapFileTopString << "\n"
	     << editorVersion << "\n"
	     << "\n";
	
	// Dimensions
	fout << width << " " << height << "\n";
	
	list<QPoint> playerPositions;
	typedef pair<QPoint, int> PPI;
	list<PPI> objectPositions;
	
	// Terrain
	QSet<int> uniqueTerrains;
	for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			auto& tile = tiles[row][col];
			int id = tile.terrain->id;
			uniqueTerrains.insert(id);
			
			fout << setw(2) << id << " ";
			
			if (tile.object)
			{
				if (int objectId = tile.object->id)
					objectPositions.emplace_back(make_pair(QPoint(col, row), objectId));
				else
					playerPositions.emplace_back(col, row);
			}
		}
		fout << "\n";
	}
	fout << "\n";
	
	// Terrain descriptions
	fout << uniqueTerrains.size() << "\n";
	for (int id : uniqueTerrains)
	{
		string name = terrainInfos[id].name.toStdString();
		float retard = terrainInfos[id].retard;
		fout << id << " "
		     << name << " "
		     << retard << "\n";
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
	for (auto&& pos_id : objectPositions)
	{
		fout << pos_id.first.x() << " " << pos_id.first.y() << " "
		     << "gold" << " " << 100000 << "\n";
	}
	
	fout.close();
	return true;
}

bool MapInfo::LoadFromFile(const QString& fileName)
{
	name = QFileInfo(fileName).completeBaseName();
	
	using namespace std;
	ifstream fin(fileName.toLocal8Bit());
	
	char cString[100];
	
	// Top string
	fin.getline(cString, 100);
	if (strcmp(cString, mapFileTopString) != 0)
		return false;
	
	// Version
	fin.getline(cString, 100);
	if (strcmp(cString, editorVersion) != 0)
		return false;
	
	// Dimensions
	fin >> width >> height;
	if (width > 200 || height > 200)
		return false;
	
	// Map content
	tiles.reserve(height);
	for (int row = 0; row < height; ++row)
	{
		tiles.push_back(QList<Tile>());
		auto& t = tiles.back();
		t.reserve(width);
		for (int col = 0; col < width; ++col)
		{
			int id;
			fin >> id;
			t.push_back({terrInfos[id], nullptr});
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
		tiles[row][col].object = objInfos[0];
	}
	
	// Resources
	fin >> n;
	for (int i = 0; i < n; ++i)
	{
		int row, col, amount;
		string name;
		fin >> col >> row >> name >> amount;
		tiles[row][col].object = objInfos[1];
	}
	
	fin.close();
	return true;
}