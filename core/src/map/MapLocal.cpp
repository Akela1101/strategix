#include "MapFull.h"
#include "MapsPathsFinder.h"
#include "player/Player.h"

#include "MapLocal.h"


namespace strategix
{

MapLocal::MapLocal(Player* player, MapFull* mapFull)
		: Map(*static_cast<Map*>(mapFull))
		, player(player)
		, mapFull(mapFull)
		, initialPosition(mapFull->GetInitialPostion(player->GetPlayerNumber()))
		, pathsFinder(new MapsPathsFinder(*this)) {}

s_p<MapsPath> MapLocal::FindPath(MapCoord from, MapCoord till) const
{
	return pathsFinder->FindPath(from, till);
}

float MapLocal::PickResource(Mine* mine, float amount)
{
	return mapFull->PickResource(mine, amount);
}

void MapLocal::RemoveMine(Mine* mine)
{
	player->RemoveMine(mine);
	GetCell(mine->GetCoord()).mine.reset();
}

}
