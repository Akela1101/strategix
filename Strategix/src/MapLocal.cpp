/* 
 * File:   MapLocal.cpp
 * Author: Akela1101
 * 
 * Created on 24 Март 2011 г., 14:02
 */

#include "MapFull.h"
#include "MapsPathsFinder.h"
#include "Player.h"
#include "PlayerSlot.h"

#include "MapLocal.h"


namespace Strategix
{

MapLocal::MapLocal(Player *player, MapFull *mapFull)
	:
	Map(*static_cast<Map*>(mapFull)),
	player(player),	
	mapFull(mapFull),
	initialPosition(mapFull->GetInitialPostion(player->playerNumber)),
	pathsFinder(new MapsPathsFinder(*this))
{}

sh_p<MapsPath> MapLocal::FindPath(const MapCoord from, const MapCoord till)
{
	return pathsFinder->FindPath(from, till);
}

float MapLocal::PickResource(sh_p<MapResource> mapResource, const float amount)
{
	return mapFull->PickResource(mapResource, amount);
}

void MapLocal::RemoveMapResource(sh_p<MapResource> mapResource)
{
	player->RemoveMapResource(mapResource);
	GetCell(mapResource->mapCoord).mapResource.reset();
}

}
