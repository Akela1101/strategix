#ifndef MAPINFO_H
#define MAPINFO_H

#define ELPP_QT_LOGGING

#include <nya/api.hpp>
#include <QPixmap>
#include <QString>


namespace map_info
{
using namespace std;

extern const char editorTitle[];
extern const char editorVersion[];
extern const char mapFileTopString[];
extern const char terrainsDefinitionFileName[];
extern const char configDir[];
extern const char imagesPath[];


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
	string name;
	QPixmap image;
	
	ToolInfo() = default;
	ToolInfo(ToolType type, const string& name, const QPixmap& image)
			: type(type), name(name), image(image) {}
};

struct TerrainInfo : ToolInfo
{
	int id; // definition - picture link
	float retard;
};

struct MapInfo
{
	static umap<string, u_p<TerrainInfo>> terrainInfos;
	static umap<ToolType, u_p<ToolInfo>> objectInfos;
	
	struct Tile
	{
		ToolInfo* terrain;
		ToolInfo* object; // can be null
	};
	
	QString name;
	int width, height;
	vector<vector<Tile>> tiles;
	
	
	MapInfo(const QString& name, int width, int height);
	MapInfo(const QString& fileName);
	
	static TerrainInfo* GetTerrainById(int id);
	
	bool SaveToFile(const QString& fileName) const;
	
private:
	void LoadFromFile(const QString& fileName);
	void CheckDimentions();
};

}

#endif //MAPINFO_H
