#pragma once

#include <Strategix_fwd.h>

namespace strx
{
using PlannedPlayers = vector<s_p<PlayerMessage>>;
using Players = umap<PlayerId, u_p<Player>>;

class Game : boost::noncopyable
{
	s_p<Map> map;                  /// global map
	umap<int, PlayerId> playerIds; /// { spot - id }
	PlannedPlayers plannedPlayers; /// players going to join
	Players players;               /// players in game

public:
	Game(const string& mapName);

	Players& GetPlayers() { return players; }
	void ReceiveMessage(s_p<Message> message, PlayerId playerId);

private:
	s_p<MapMessage> CreateMapMessage(int playerSpot);
	void LoadMap(const string& mapName);
	void AddPlayer(s_p<Message> message, PlayerId playerId);
	void Ready(PlayerId playerId);
	void Start();
};

}
