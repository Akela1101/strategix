#pragma once

#include <Strategix_fwd.h>


namespace strx
{

class MapManager : boost::noncopyable
{
	const string mapsPath;  /// usually "maps"
	u_p<Map> map;           /// global map
	
public:
	MapManager(string mapsPath) : mapsPath(mapsPath) {}
	~MapManager();
	
	const string& GetMapsDirectory() const { return mapsPath; }
	bool HasMap() const { return map.get(); }
	void LoadMap(const string& mapName);
	
	/// @#~ should return reference to map AND fog of war mask
	Map& CreateMap(int playerId);
	
private:
	string GetFilePath(const string& name) const;
};
}
