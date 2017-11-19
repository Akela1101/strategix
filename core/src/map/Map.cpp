#include <map/MapManager.h>
#include <map/MapsPath.h>
#include <map/MapsPathsFinder.h>
#include <map/Mine.h>
#include <player/Player.h>

#include "Map.h"


namespace strategix
{
Map::Map(MapManager* mapFull)
		: mapManager(mapFull)
		, pathsFinder(new MapsPathsFinder(*this)) {}

Map::~Map() = default;

u_p<MapsPath> Map::FindPath(MapCoord from, MapCoord till) const
{
	return pathsFinder->FindPath(from, till);
}

ResourceUnit Map::PickResource(Mine* mine, ResourceUnit amount)
{
	return mine->PickResource(amount);
}

void Map::RemoveMine(Mine* mine)
{
	player->RemoveMine(mine);
	//GetCell(mine->GetCoord()).mine.reset();
}

}
