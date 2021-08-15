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
	ResourcesContext resourcesContext;

	u_p<Game> game;

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
	 * Join the game.
	 * @param gameId game id
	 */
	void JoinGame(GameId gameId);

	/**
	 * Add available maps and games to user interface.
	 */
	virtual void HandleContext(const ContextMessage* message) = 0;

	/**
	 * Update one game in the list of open games.
	 * @param gameMessage game information
	 */
	virtual void HandleGame(const GameMessage* gameMessage) = 0;

	/**
	 * Create game.
	 * @param resourcesContext resource infos
	 * @return game object
	 */
	virtual u_p<Game> CreateGame(ResourcesContext resourcesContext) = 0;
};
}  // namespace strx
