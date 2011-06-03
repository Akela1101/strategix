/* 
 * File:   MapLocal.cpp
 * Author: Akela1101
 * 
 * Created on 24 Март 2011 г., 14:02
 */

#include "MapFull.h"
#include "MapsPathsFinder.h"
#include "Player.h"

#include "MapLocal.h"

namespace Strategix
{

MapLocal::MapLocal(Player *player, MapFull *mapFull)
	:
	player(player),
	Map(*static_cast<Map*>(mapFull)),
	mapFull(mapFull),
	initialPosition(mapFull->GetInitialPostion(player->playerNumber)),
	pathsFinder(new MapsPathsFinder(*this))
{}

sh_p<MapsPath> MapLocal::FindPath(const MapCoord from, const MapCoord till)
{
	return pathsFinder->FindPath(from, till);
}

}
