#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/irange.hpp>
#include <boost/filesystem.hpp>
#include <QBitmap>
#include <strx/map/Map.h>

#include "MapInfo.h"


namespace map_info
{
using namespace strx;
namespace fs = boost::filesystem;


const char terrainsDefFileName[] = "terrains.def";
const char objectsDefFileName[] = "objects.def";
const char configDir[] = "config/";
const char imagesPath[] = "config/images/";
const char mapConfigPath[] = "config/map/";

umap<string, ToolInfo> MapInfo::terrainTools;
umap<string, ToolInfo> MapInfo::objectTools;
vector<QPixmap> MapInfo::playerMarks;


const QPixmap& MapInfo::GetPlayerMark(int playerNumber)
{
	if (playerMarks.empty())
		nya_throw << "Call LoadObjectTools() first.";
	
	return playerMarks[playerNumber < playerMarks.size() ? playerNumber : 0];
}

#define Q_REG_TYPE(type) qRegisterMetaType<type>(#type);
void MapInfo::QRegisterTypes()
{
	Q_REG_TYPE(RealCoord);
}

void MapInfo::LoadTerrainTools()
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
		string name;
		float retard;
		fin >> retard >> name;
		if (name.empty()) break;
		
		Map::AddTerrain(make_u<Map::Terrain>(i, name, retard));
		
		int col = i % divs, row = i / divs;
		QPixmap image = pixmap.copy(col * tileSize, row * tileSize, tileSize, tileSize);
		terrainTools.emplace(name, ToolInfo(ToolType::TERRAIN, name, image));
	}
	fin.close();
}

void MapInfo::LoadObjectTools()
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
		string typeName, imageFileName, imageSubdir;
		fin >> typeName >> imageFileName;
		if (typeName.empty()) break;
		
		ToolType type = typeName;
		switch (type)
		{
			case ToolType::MINE:
				imageSubdir = "mines/";
				break;
			case ToolType::ENTITY:
				imageSubdir = "objects/";
				break;
			default:
				nya_throw << "Cannot handle map object of type: " << typeName;
		}
		
		string name = path(imageFileName).stem().string();
		string pixmapPath = (path(mapConfigPath) / imageSubdir / imageFileName).string();
		
		objectTools.emplace(name, ToolInfo(type, name, LoadPixmap(pixmapPath)));
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
		playerMark.fill((Qt::GlobalColor) color);
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

}