#include <strx/map/Map.h>

#include "MapManager.h"


namespace strx
{
MapManager::~MapManager() = default;

void MapManager::LoadMap(const string& mapName)
{
	string path = GetFilePath(mapName);
	baseMap.reset(new BaseMap(path, mapName));
}

u_p<Map> MapManager::CreateMap(Player& player)
{
	return make_u<Map>(*baseMap, player);
}

string MapManager::GetFilePath(const string& name) const
{
	namespace fs = boost::filesystem;
	
	auto fileName = boost::str(boost::format("%s.map") % name);
	return (fs::path(mapsDirectory) / fileName).string();
}

}
