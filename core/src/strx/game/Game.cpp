#include <boost/filesystem.hpp>
#include <strx/kernel/ConfigManager.h>
#include <strx/kernel/Kernel.h>
#include <strx/kernel/Message.h>
#include <strx/map/Map.h>
#include <strx/player/Player.h>

#include "Game.h"

namespace strx
{
Game::Game(const string& mapName)
{
	string mapsPath = ConfigManager::GetMapsPath();
	if (mapsPath.empty()) nya_throw << "Configuration should be loaded before adding game.";

	LoadMap(mapName);
}

void Game::ReceiveMessage(s_p<Message> message, PlayerId playerId)
{
	switch (message->GetType())
	{
	case Message::Type::PLAYER: AddPlayer(move(message), playerId); break;
	case Message::Type::START: Ready(playerId); break;
	default: players[playerId]->ReceiveMessage(move(message));
	}
}

s_p<MapMessage> Game::CreateMapMessage(int playerSpot)
{
	// @#~ should return map AND fog-of-war mask
	ignore = playerSpot;
	return make_s<MapMessage>(map);
}

void Game::LoadMap(const string& mapName)
{
	string mapsPath = ConfigManager::GetMapsPath();
	string fileName = boost::str("%s.map"s % mapName);
	string path = (boost::filesystem::path(mapsPath) / fileName).string();

	map.reset(new Map(path));
}

void Game::AddPlayer(s_p<Message> message, PlayerId playerId)
{
	auto playerMessage = sp_cast<PlayerMessage>(message);
	int playerSpot = playerMessage->spot;
	if (in_(playerSpot, playerIds)) // replace is not supported yet
		nya_throw << "Trying to add same player twice [%d], name: %s"s % playerSpot % playerMessage->name;

	playerIds.emplace(playerSpot, playerId);
	plannedPlayers.push_back(playerMessage);

	Kernel::SendMessageAll(move(playerMessage));
}

void Game::Ready(PlayerId playerId)
{
	//TODO: check all players are ready
	Start();
}

void Game::Start()
{
	for (const auto& plannedPlayer : plannedPlayers)
	{
		int playerSpot = plannedPlayer->spot;
		PlayerId playerId = playerIds[playerSpot];

		// map
		auto&& mapMessage = CreateMapMessage(playerSpot);
		Map& map = *mapMessage->map;
		if (plannedPlayer->type == PlayerType::HUMAN)
		{
			Kernel::SendMessageOne(move(mapMessage), playerId);
		}

		// player
		auto player = make_u<Player>(*plannedPlayer, playerId, map);
		player->Start();
		players.emplace(playerId, move(player));
	}
	plannedPlayers.clear();
}

}
