#ifndef _MAPMANAGER_H
#define _MAPMANAGER_H

#include <strx/common/Strategix_Forward.h>


namespace strx
{

class MapManager
{
	string mapName;                /// map name
	u_p<BaseMap> baseMap;          /// general map information
	umap<Mine*, u_p<Mine>> mines;  /// all mines
	int playersNumber;             /// number of players
	vector<MapCoord> initialPositions; /// player initial positions
	
public:
	MapManager(const string& mapName);
	MapManager(const MapManager& _c) = delete;
	MapManager& operator=(const MapManager& _c) = delete;
	~MapManager();
	
	const string& GetMapName() const { return mapName; }
	
	u_p<Map> CreateMap(Player& player);
	void RemoveResource(Mine* mine);
	
private:
	string GetFilePath(const string& name) const;
};
}

#endif // _MAPMANAGER_H

