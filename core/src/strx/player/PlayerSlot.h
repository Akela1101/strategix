#pragma once

#include "Strategix_fwd.h"


namespace strx
{
/**
 * Class holding player state.
 * Derive from this class to receive player events.
 *
 * This class belongs to strategix, so shouldn't be deleted by user.
 */
class PlayerSlot : boost::noncopyable
{
	s_p<PlayerMessage> playerMessage;

public:
	PlayerSlot(s_p<PlayerMessage> playerMessage) : playerMessage(move(playerMessage)) {}
	virtual ~PlayerSlot() = default;

	/// @return unique name
	const string& GetName() const;

	/// @return player spot
	int GetSpot() const;

	/// @return [human | ai | net]
	PlayerType GetType() const;
};
}  // namespace strx
