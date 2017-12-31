#include <strx/map/Map.h>
#include <strx/kernel/Message.h>

#include "MapManager.h"


namespace strx
{
void MapManager::LoadMap(const string& mapName)
{
	string path = GetFilePath(mapName);
	map.reset(new Map(path));
}

s_p<MapMessage> MapManager::CreateMapMessage(int playerId)
{
	return make_s<MapMessage>(map);
}

string MapManager::GetFilePath(const string& name) const
{
	namespace fs = boost::filesystem;

	auto fileName = boost::str("%s.map"s % name);
	return (fs::path(mapsPath) / fileName).string();
}

}
