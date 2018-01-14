#pragma once

#include <Strategix_fwd.h>

namespace strx
{
/**
 * Game representation on client.
 */
class GameSlot : boost::noncopyable
{
	ResourceInfosType resourceInfos;
	umap<int, s_p<PlayerMessage>> registeredPlayers;
	umap<int, u_p<PlayerSlot>> players;
	umap<IdType, u_p<EntitySlot>> entities;

public:
	GameSlot();
	virtual ~GameSlot();

	const ResourceInfosType& GetResourceInfos() const { return resourceInfos; }
	EntitySlot& GetEntitySlot(IdType id);

	static void SendMessageOne(s_p<Message> message);

	/**
	 * Called in network thread, thus should call ReceiveMessage() in game thread.
	 */
	virtual void MessageReceived(s_p<Message> message) = 0;

protected:
	/**
	 * Must be called from MessageReceived().
	 */
	void ReceiveMessage(s_p<Message> message);

	/**
	 * Update one game in the list of open games.
	 * @param gameId game id
	 * @param gameMessage game information, null if removed.
	 */
	virtual void GameUpdated(int gameId, const GameMessage* gameMessage) = 0;

	/**
	 * Start new game.
	 * @param mapMessage map holder
	 */
	virtual void StartGame(s_p<Map> map);

	/// create player slot
	virtual u_p<PlayerSlot> AddPlayer(s_p<PlayerMessage> playerMessage) = 0;

	/// add entity to map
	virtual u_p<EntitySlot> AddEntity(s_p<EntityMessage> entityMessage) = 0;

	/// player resources change
	virtual void ResourcesChanged(const Resources& newResources) {}

	/// mine amount changed
	virtual void MineAmountChanged(IdType id, ResourceUnit amount) {}

	/// object removed
	virtual void ObjectRemoved(IdType id) = 0;
};
}
