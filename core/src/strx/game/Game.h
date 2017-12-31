#pragma once

#include <Strategix_fwd.h>

namespace strx
{
using PlayersType = umap<string, u_p<Player>>;

class Game : boost::noncopyable
{
	vector<s_p<PlayerMessage>> plannedPlayers; /// players going to join
	umap<int, NetId> playerNetIds; /// player network ids
	PlayersType players;           /// players in game

public:
	PlayersType& GetPlayers() { return players; }

	void AddPlayer(s_p<PlayerMessage> playerMessage, NetId netId);
	void Start(MapManager& mapManager);
};

}
