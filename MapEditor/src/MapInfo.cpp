/* 
 * File:   MapInfo.cpp
 * Author: Akela1101
 * 
 * Created on 8 Сентябрь 2010 г., 23:19
 */

#include "MapInfo.h"

#include <fstream>
#include <list>
#include <QtGui/qmessagebox.h>

extern const char mapFileTopString[];
extern const char terrainsDefinitionFileName[];

std::map<int, sh_p<ObjectInfo> > MapInfo::terrInfos;
std::map<int, sh_p<ObjectInfo> > MapInfo::objInfos;

MapInfo::MapInfo(const std::string &name, const int width, const int height)
	:name(name), width(width), height(height)
{
	tiles.reset(new sh_a<Tile>[height]);
	for( int row = 0; row < height; ++row )
	{
		tiles[row].reset(new Tile[width]);
		for( int col = 0; col < width; ++col )
		{
			tiles[row][col].terrain = terrInfos[10];
		}
	}
}

MapInfo::MapInfo(const QString &fileName)
{
	if( !LoadFromFile(fileName) )
		QMessageBox::critical(0, "Unable to open file!", "May be wrong file format or version...");
}

MapInfo::~MapInfo()
{
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

	// Dimentions
	fout << width << " " << height << endl;

	list<QPoint> playerPositions;
	typedef pair<QPoint, int> PPI;
	list<PPI> objectPositions;

	// Terrain
	for( int row = 0; row < height; ++row )
	{
		for( int col = 0; col < width; ++col )
		{
			MapInfo::Tile &tile = tiles[row][col];
			fout << tile.terrain->id << " ";
			if( tile.object )
			{
				int id = tile.object->id;
				if( !id )
				{
					playerPositions.push_back(QPoint(col, row));
				}
				else
				{
					objectPositions.push_back(make_pair(QPoint(col, row), id));
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

	// Objects
	fout << objectPositions.size() << endl;
	foreach(PPI pa, objectPositions)
	{
		fout << pa.first.x() << " " << pa.first.y() << " " << pa.second << endl;
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
	if( strcmp(cString, mapFileTopString) )
		return false;

	fin.getline(cString, 100);
//	if( strcmp(cString, terrainsDefinitionFileName) )
//		return false;

	// Name
	fin.getline(cString, 100);
	name = cString;

	// Dimentions
	fin >> width >> height;
	if( width > 200 || height > 200 )
		return false;

	// Terrain
	int id;
	tiles.reset(new sh_a<Tile>[height]);
	for( int row = 0; row < height; ++row )
	{
		tiles[row].reset(new Tile[width]);
		for( int col = 0; col < width; ++col )
		{
			fin >> id;
			tiles[row][col].terrain = terrInfos[id];
		}
	}

	int size, row, col;
	// Player initial positions
	fin >> size;
	for( int i = 0; i < size; ++i )
	{
		fin >> col >> row;
		tiles[row][col].object = objInfos[0];
	}

	// Objects
	fin >> size;
	for( int i = 0; i < size; ++i )
	{
		fin >> col >> row >> id;
		tiles[row][col].object = objInfos[id];
	}

	fin.close();
	return true;
}