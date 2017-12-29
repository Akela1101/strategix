#pragma once

#define ELPP_QT_LOGGING

#include <nya/api.hpp>
#include <strx/common/StrategixCommon.h>
#include <strx/map/Map.h>
#include <MapInfo_fwd.h>
#include <QPixmap>
#include <QString>


namespace map_info
{
struct ToolInfo
{
	ToolType type;
	string name;
	QPixmap image;

	ToolInfo() = default;
	ToolInfo(ToolType type, string name, QPixmap image) : type(type), name(move(name)), image(move(image)) {}
};

struct MapInfo
{
	static Map::TerrainsType terrains;
	static umap<string, ToolInfo> terrainTools;
	static umap<string, ToolInfo> objectTools;
	static vector<QPixmap> playerMarks;

	static const QPixmap& GetPlayerMark(int playerNumber);
	static void QRegisterTypes();
	static void LoadTerrainTools();
	static void LoadObjectTools();
	static QPixmap LoadPixmap(const string& path);
};

}
