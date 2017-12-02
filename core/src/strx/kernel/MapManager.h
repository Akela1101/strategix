#ifndef _MAPMANAGER_H
#define _MAPMANAGER_H

#include <Strategix_Forward.h>


namespace strx
{

class MapManager
{
	const string mapsDirectory;    /// usually "maps"
	u_p<Map> map;          /// global map
	
public:
	MapManager(string mapsDirectory) : mapsDirectory(mapsDirectory) {}
	MapManager(const MapManager& _c) = delete;
	MapManager& operator=(const MapManager& _c) = delete;
	~MapManager();
	
	const string& GetMapsDirectory() const { return mapsDirectory; }
	void LoadMap(const string& mapName);
	u_p<Map> CreateMap(int playerId);
	
private:
	string GetFilePath(const string& name) const;
};
}

#endif // _MAPMANAGER_H

