#ifndef _MAPMANAGER_H
#define _MAPMANAGER_H

#include "common/Strategix_Forward.h"


namespace strategix
{

class MapManager
{
	string mapName;
	u_p<Map> map;
	umap<Mine*, u_p<Mine>> mines;        // all mines
	int nPlayers;
	vector<MapCoord> initialPositions;
	
public:
	MapManager(const string& mapName);
	MapManager(const MapManager& _c) = delete;
	MapManager& operator=(const MapManager& _c) = delete;
	~MapManager();
	
	const string& GetMapName() const { return mapName; }
	MapCoord GetInitialPostion(int iPlayer) const { return initialPositions[iPlayer]; }
	
	u_p<Map> CreateMap(Player* player);
	void RemoveResource(Mine* mine);
	
private:
	string GetFilePath(const string& name) const;
};
}

#endif // _MAPMANAGER_H

