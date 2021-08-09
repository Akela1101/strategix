#pragma once

#include "../../strx/strx_fwd.hpp"

namespace strx
{
using Players = umap<PlayerId, u_p<PlayerKernel>>;

class GameKernel : boost::noncopyable
{
	using PlannedPlayers = vector<s_p<PlayerMessage>>;

	s_p<Map> map;                              ///< global map
	umap<int, PlayerId> spotIds;               ///< { spot - id }
	PlannedPlayers plannedPlayers;             ///< players going to join
	uset<PlayerId> readyPlayers;               ///< players ready to start
	Players players;                           ///< players in game
	umap<IdType, s_p<EntityKernel>> entities;  ///< all entities
	vector<IdType> removedEntities;            ///< entities removed at the end of Tick

public:
	GameKernel(const string& mapName);

	Players& GetPlayers() { return players; }
	s_p<EntityKernel> GetEntity(IdType id) const;
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

}  // namespace strx
