#pragma once

#include <Strategix_fwd.h>

namespace strx
{
using PlannedPlayers = vector<s_p<PlayerMessage>>;
using Players = umap<PlayerId, u_p<Player>>;

class Game : boost::noncopyable
{
	s_p<Map> map;                    /// global map
	umap<int, PlayerId> playerIds;   /// { spot - id }
	PlannedPlayers plannedPlayers;   /// players going to join
	uset<PlayerId> readyPlayers;     /// players ready to start
	Players players;                 /// players in game
	umap<IdType, s_p<Entity>> entities;  /// all entities
	vector<IdType> removedEntities;  /// entities removed at the end of Tick

public:
	Game(const string& mapName);

	Players& GetPlayers() { return players; }
	s_p<Entity> GetEntity(IdType id) const;
	void ReceiveMessage(s_p<Message> message, PlayerId playerId);
	void Tick(float seconds);

	void AddEntity(MapEntity* mapEntity);
	void RemoveEntity(IdType entityId);

private:
	s_p<MapMessage> CreateMapMessage(int playerSpot);
	void LoadMap(const string& mapName);
	void AddPlayer(s_p<Message> message, PlayerId playerId);
	void Ready(PlayerId playerId);
	void Start();
};

}
