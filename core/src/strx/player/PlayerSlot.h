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
	PlayerSlot(s_p<PlayerMessage> playerMessage);
	virtual ~PlayerSlot() = default;

	/// @return unique name
	const string& GetName() const;

	/// @return player id
	int GetId() const;

	/// @return [human | ai | net]
	PlayerType GetType() const;

// Callbacks:
	/// on adding entity to map
	virtual void EntityAdded(s_p<EntityMessage> entityMessage) = 0;

	/// on removing entity from map
	//virtual void EntiRemoved(Entity* entity) = 0;

	/// on holding resources change
	virtual void ResourcesChanged(const Resources& newResources) {}

	/// on mine amount changed
	virtual void MineAmountChanged(IdType id, ResourceUnit amount) {}

	/// on mine removed
	virtual void MineRemoved(IdType id) {}
};
}
