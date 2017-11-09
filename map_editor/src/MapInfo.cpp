#include "MapInfo.h"

#include <fstream>
#include <QMessageBox>

using namespace std;

extern const char mapFileTopString[];
extern const char terrainsDefinitionFileName[];

map<int, s_p<ObjectInfo>> MapInfo::terrInfos;
map<int, s_p<ObjectInfo>> MapInfo::objInfos;

MapInfo::MapInfo(const string& name, size_t width, size_t height)
		: name(name), width(width), height(height)
{
	tiles.resize(height);
	for (int row = 0; row < height; ++row)
	{
		tiles[row].resize(width);
		for (int col = 0; col < width; ++col)
		{
			tiles[row][col].terrain = terrInfos[10];
		}
	}
}

MapInfo::MapInfo(const QString& fileName)
{
	if (!LoadFromFile(fileName))
		QMessageBox::critical(nullptr, "Unable to open file!", "May be wrong file format or version...");
}

bool MapInfo::SaveToFile(QString fileName) const
{
	using namespace std;
	ofstream fout(fileName.toLocal8Bit());
	
	// Name
	fout << mapFileTopString << endl;
	fout << terrainsDefinitionFileName << endl;
	fout << name << endl;
	fout << endl;
	
	// Dimensions
	fout << width << " " << height << endl;
	
	list<QPoint> playerPositions;
	typedef pair<QPoint, int> PPI;
	list<PPI> objectPositions;
	
	// Terrain
	for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			auto& tile = tiles[row][col];
			fout << tile.terrain->id << " ";
			if (tile.object)
			{
				int id = tile.object->id;
				if (!id)
				{
					playerPositions.emplace_back(col, row);
				}
				else
				{
					objectPositions.emplace_back(make_pair(QPoint(col, row), id));
				}
			}
		}
		fout << endl;
	}
	fout << endl;
	
	// Player initial positions
	fout << playerPositions.size() << endl;
			foreach(QPoint p, playerPositions)
		{
			fout << p.x() << " " << p.y() << endl;
		}
	fout << endl;
	
	// Resources
	fout << objectPositions.size() << endl;
			foreach(PPI pa, objectPositions)
		{
			fout << pa.first.x() << " " << pa.first.y() << " "
			     << "gold" << " " << 100000 << endl; // @#~!!!!!!!!
		}
	
	fout.close();
	return true;
}

bool MapInfo::LoadFromFile(QString fileName) // @#~ Make errors more verbose !!!
{
	using namespace std;
	ifstream fin(fileName.toLocal8Bit());
	
	char cString[100];
	fin.getline(cString, 100);
	if (strcmp(cString, mapFileTopString))
		return false;
	
	fin.getline(cString, 100);
//	if( strcmp(cString, terrainsDefinitionFileName) )
//		return false;
	
	// Name
	fin.getline(cString, 100);
	name = string(cString);
	
	// Dimensions
	fin >> width >> height;
	if (width > 200 || height > 200)
		return false;
	
	// Terrain
	int id;
	tiles.resize(height);
	for (int row = 0; row < height; ++row)
	{
		tiles[row].resize(width);
		for (int col = 0; col < width; ++col)
		{
			fin >> id;
			tiles[row][col].terrain = terrInfos[id];
		}
	}
	
	// Player initial positions
	int size, row, col;
	fin >> size;
	for (int i = 0; i < size; ++i)
	{
		fin >> col >> row;
		tiles[row][col].object = objInfos[0];
	}
	
	// Resources
	string name;
	int amount;
	fin >> size;
	for (int i = 0; i < size; ++i)
	{
		fin >> col >> row >> name >> amount;// @#~!!!!!!!!
		tiles[row][col].object = objInfos[1];
	}
	
	fin.close();
	return true;
}