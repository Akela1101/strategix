#include <strx/kernel/Kernel.h>
#include <strx/kernel/MapManager.h>
#include <strx/kernel/Message.h>
#include <strx/player/Player.h>

#include "Game.h"

namespace strx
{
void Game::AddPlayer(s_p<PlayerMessage> playerMessage, NetId netId)
{
	int playerId = playerMessage->id;
	if (in_(playerId, playerNetIds)) // replace is not supported yet
		nya_throw << "Trying to add same player twice [%d], name: %s"s % playerId % playerMessage->name;

	playerNetIds.emplace(playerId, netId);
	plannedPlayers.push_back(move(playerMessage));
}

void Game::Start(MapManager& mapManager)
{
	if (!mapManager.HasMap()) nya_throw << "Map should be loaded before adding player.";

	for (const auto& plannedPlayer : plannedPlayers)
	{
		int playerId = plannedPlayer->id;
		NetId netId = playerNetIds[playerId];

		// map
		auto&& mapMessage = mapManager.CreateMapMessage(playerId);
		Map& map = *mapMessage->map;
		if (plannedPlayer->type == PlayerType::HUMAN)
		{
			Kernel::SendMessageOne(move(mapMessage), netId);
		}

		// player
		auto player = make_u<Player>(*plannedPlayer, netId, map);
		player->Start();
		players.emplace(player->GetName(), move(player));
	}
	plannedPlayers.clear();
}
}
