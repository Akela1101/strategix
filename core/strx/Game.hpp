#pragma once

#include <nya/enum.hpp>

#include "strx_fwd.hpp"

namespace strx
{
/**
 * Game representation on client.
 */
class Game : boost::noncopyable
{
	ResourcesContext resourcesContext;
	umap<int, s_p<PlayerMessage>> registeredPlayers;
	umap<int, u_p<Player>> players;
	umap<IdType, u_p<Entity>> entities;

public:
	Game(ResourcesContext resourcesContext) : resourcesContext(move(resourcesContext)) {}
	virtual ~Game();

	const ResourcesContext& GetResourcesContext() const { return resourcesContext; }
	Entity& GetEntitySlot(IdType id) { return *entities[id]; }

	static void SendMessageOne(s_p<Message> message);

	/**
	 * @param game related message
	 */
	void ReceiveMessage(s_p<Message> message);

protected:
	/// prepare map view
	virtual void OnMapReceived(s_p<Map> map);

	/// show game screen
	virtual void OnGameStarted() = 0;

	/// create player slot
	virtual u_p<Player> OnPlayerAdded(s_p<PlayerMessage> playerMessage) = 0;

	/// add entity to map
	virtual u_p<Entity> OnEntityAdded(s_p<EntityMessage> entityMessage) = 0;

	/// player resources change
	virtual void OnResourcesChanged(const Resources& newResources) {}

	/// mine amount changed
	virtual void OnMineAmountChanged(IdType id, ResourceUnit amount) {}

	/// object removed
	virtual void OnObjectRemoved(IdType id) = 0;
};
}  // namespace strx
