#ifndef _PLAYERSLOT_H
#define    _PLAYERSLOT_H

#include "Strategix_Forward.h"


namespace strx
{
/**
 * Class holding player state.
 * Derive from this class to receive player events.
 *
 * This class belongs to strategix, so shouldn't be deleted by user.
 */
class PlayerSlot
{
	friend class Player;
	Player* player;
	
public:
	PlayerSlot(Player* player);
	virtual ~PlayerSlot();
	PlayerSlot(const PlayerSlot& _c) = delete;
	PlayerSlot& operator=(const PlayerSlot& _c) = delete;
	
	/// @return unique name
	const string& GetName() const;
	
	/// @return [human | ai | net]
	PlayerType GetType() const;

protected:
// Callbacks:
	/// on adding entity to map
	virtual void EntiAdded(Enti* enti) = 0;
	
	/// on removing entity from map
	virtual void EntiRemoved(Enti* enti) = 0;
	
	/// on holding resources change
	virtual void ResourcesChanged(Resources* newResources) = 0;
};
}

#endif    /* _PLAYERSLOT_H */

