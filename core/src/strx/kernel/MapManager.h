#ifndef _MAPMANAGER_H
#define _MAPMANAGER_H

#include <Strategix_Forward.h>


namespace strx
{

class MapManager : boost::noncopyable
{
	const string mapsDirectory;  /// usually "maps"
	u_p<Map> map;                /// global map
	
public:
	MapManager(string mapsDirectory) : mapsDirectory(mapsDirectory) {}
	~MapManager();
	
	const string& GetMapsDirectory() const { return mapsDirectory; }
	bool HasMap() const { return map.get(); }
	void LoadMap(const string& mapName);
	
	/// @#~ should return reference to map AND fog of war mask
	Map& CreateMap(int playerId);
	
private:
	string GetFilePath(const string& name) const;
};
}

#endif // _MAPMANAGER_H

