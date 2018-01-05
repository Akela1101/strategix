#pragma once

#include <Strategix_fwd.h>

namespace strx
{
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
	virtual void MessageReceived(s_p<Message> message) = 0;

protected:
	void ReceiveMessage(s_p<Message> message);

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

	/// removing entity from map
	//virtual void EntiRemoved(Entity* entity) = 0;

	/// mine amount changed
	virtual void MineAmountChanged(IdType id, ResourceUnit amount) {}

	/// mine removed
	virtual void MineRemoved(IdType id) {}
};
}
