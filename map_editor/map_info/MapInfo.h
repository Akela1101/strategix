#ifndef MAPINFO_H
#define MAPINFO_H

#define ELPP_QT_LOGGING

#include <nya/api.hpp>
#include <nya/enum.hpp>
#include <QPixmap>
#include <QString>


namespace map_info
{
using namespace std;

extern const char editorVersion[];
extern const char mapFileTopString[];
extern const char configDir[];
extern const char imagesPath[];


#define ToolTypeDef(K, V)                      \
	K(TERRAIN)  /* terrain */                  \
	K(OBJECT)   /* map objects */              \
	K(MINE)     /* resource mine */
nya_enum(ToolType, ToolTypeDef)


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
	struct Object
	{
		ToolInfo& info;
		
		Object(ToolInfo& info) : info(info) {}
		virtual ~Object() {}
	};
	struct PlayerObject : Object
	{
		int owner;        // owner player id
		
		PlayerObject(ToolInfo& info, int owner) : Object(info), owner(owner) {}
	};
	struct MineObject : Object
	{
		int amount;       // resource amount
		
		MineObject(ToolInfo& info, int amount) : Object(info), amount(amount) {}
	};
	
	struct Tile
	{
		ToolInfo* terrain;
		u_p<Object> object; // can be null
	};
	
	static umap<string, u_p<TerrainInfo>> terrainInfos;
	static umap<string, u_p<ToolInfo>> objectInfos;
	static vector<QPixmap> playerMarks;

	QString name;
	int width, height;
	vector<vector<Tile>> tiles;
	
	
	MapInfo(const QString& name, int width, int height);
	MapInfo(const QString& fileName);
	
	static TerrainInfo* GetTerrainById(int id) noexcept;
	static const QPixmap& GetPlayerMark(int playerNumber);
	static void LoadTerrainInfos();
	static void LoadObjectInfos();
	static QPixmap LoadPixmap(const string& path);
	
	void SaveToFile(const QString& fileName) const;
	
private:
	void LoadFromFile(const QString& fileName);
	void CheckDimentions();
};

}

#endif //MAPINFO_H
