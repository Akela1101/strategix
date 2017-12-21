#include <strx/map/Map.h>

#include "MapManager.h"


namespace strx
{
MapManager::~MapManager() = default;

void MapManager::LoadMap(const string& mapName)
{
	string path = GetFilePath(mapName);
	map.reset(new Map(path, mapName));
}

Map& MapManager::CreateMap(int playerId)
{
	return *map;
}

string MapManager::GetFilePath(const string& name) const
{
	namespace fs = boost::filesystem;
	
	auto fileName = boost::str(boost::format("%s.map") % name);
	return (fs::path(mapsPath) / fileName).string();
}

}
