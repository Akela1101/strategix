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
#define GameStageEnumDef(K, V)       \
	K(NONE)    /* no game started */ \
	K(STARTED) /* started */
	nya_enum(GameStage, GameStageEnumDef);

	GameStage stage = GameStage::NONE;
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
	/**
	 * Start new game.
	 * @param mapMessage map holder
	 */
	virtual void StartGame(s_p<Map> map);

	/// create player slot
	virtual u_p<Player> AddPlayer(s_p<PlayerMessage> playerMessage) = 0;

	/// add entity to map
	virtual u_p<Entity> AddEntity(s_p<EntityMessage> entityMessage) = 0;

	/// player resources change
	virtual void ResourcesChanged(const Resources& newResources) {}

	/// mine amount changed
	virtual void MineAmountChanged(IdType id, ResourceUnit amount) {}

	/// object removed
	virtual void ObjectRemoved(IdType id) = 0;

private:
	bool CheckGameStage(const Message& message);
};
}  // namespace strx
