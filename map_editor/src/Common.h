#ifndef Common_H
#define Common_H

#include <boost/range/irange.hpp>
#include <nya/api.hpp>
#include <QPixmap>
#include <QString>


enum class ToolType
{
	NONE,      // tools like eraser
	PLAYER,    // player position
	TERRAIN,   // terrain
	MINE       // mine
};

struct ToolInfo
{
	ToolType type;
	std::string name;
	QPixmap image;
	
	ToolInfo() = default;
	ToolInfo(ToolType type, const std::string& name, const QPixmap& image)
			: type(type), name(name), image(image) {}
};

struct TerrainInfo : ToolInfo
{
	int id; // definition - picture link
	float retard;
};


namespace common
{
extern const char editorTitle[];
extern const char editorVersion[];
extern const char mapFileTopString[];
extern const char terrainsDefinitionFileName[];
extern const char configDir[];
extern const char imagesPath[];

extern umap<std::string, u_p<TerrainInfo>> terrainInfos;
extern umap<ToolType, u_p<ToolInfo>> objectInfos;

const char* str(const QString& message);
TerrainInfo* GetTerrainById(int id);
}

#endif //Common_H
