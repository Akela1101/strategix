#pragma once

#include <Strategix_fwd.h>


namespace strx
{

class MapManager : boost::noncopyable
{
	const string mapsPath;  /// usually "maps"
	s_p<Map> map;           /// global map

public:
	MapManager(string mapsPath) : mapsPath(mapsPath) {}

	const string& GetMapsDirectory() const { return mapsPath; }
	bool HasMap() const { return map.get(); }
	void LoadMap(const string& mapName);

	/// @#~ should return map AND fog-of-war mask
	s_p<MapMessage> CreateMapMessage(int playerId);

private:
	string GetFilePath(const string& name) const;
};
}
