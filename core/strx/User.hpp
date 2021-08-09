#pragma once

#include <nya/enum.hpp>

#include "strx_fwd.hpp"

namespace strx
{
/**
 * Kernel works with multiple Users.
 */
class User : boost::noncopyable
{
	ResourceInfosType resourceInfos;

	u_p<GameSlot> game;

public:
	static void SendMessageOne(s_p<Message> message);

public:
	User();
	virtual ~User();

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
	 * Add available maps and games to user interface.
	 */
	virtual void HandleContext() = 0;

	/**
	 * Update one game in the list of open games.
	 * @param gameId game id
	 * @param gameMessage game information, null if removed.
	 */
	virtual void GameUpdated(GameId gameId, const GameMessage* gameMessage) = 0;

	/**
	 * Add game.
	 * @param gameId game id
	 * @return game object
	 */
	virtual u_p<GameSlot> AddGame(GameId gameId, ResourceInfosType resourceInfos) = 0;
};
}  // namespace strx
