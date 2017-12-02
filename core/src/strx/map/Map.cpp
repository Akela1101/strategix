#include <strx/kernel/MapManager.h>
#include <strx/map/MapsPath.h>
#include <strx/map/MapsPathsFinder.h>
#include <strx/map/Mine.h>
#include <strx/player/Player.h>

#include "Map.h"


namespace strx
{
Map::Map(const BaseMap& map, Player& player)
		: BaseMap(map)
		, player(player)
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
	player.RemoveMine(mine);
	//GetCell(mine->GetCoord()).mine.reset();
}

}
