#ifndef _PLAYERSLOT_H
#define    _PLAYERSLOT_H

#include "Strategix_Forward.h"


namespace strategix
{
/**
 * Class holding player state.
 * Derive from this class to receive player events.
 *
 * This class belongs to strategix, so shouldn't be deleted by user.
 */
class PlayerSlot
{
	Player* player = nullptr;
	
	const string name;
	const PlayerType type;
	const int playerNumber;
	const string raceName;
	vector<u_p<EntiSlot>> entis;
	
public:
	PlayerSlot(string name, PlayerType type, int playerNumber, string raceName);
	virtual ~PlayerSlot();
	PlayerSlot(const PlayerSlot& _c) = delete;
	PlayerSlot& operator=(const PlayerSlot& _c) = delete;
	
	/// @return unique name
	const string& GetName() const { return name; }
	
	/// @return [human | ai | net]
	PlayerType GetType() const { return type; }
	
	/// @return number of player on the map
	int GetPlayerNumber() const { return playerNumber; }
	
	/// @return race name
	const string& GetRaceName() const { return raceName; }
	
	void AddEnti(EntiSlot* enti);
	
// Callbacks:

	/// on adding entity to map
	virtual void OnAddEnti(EntiSlot* enti) = 0;
	
	/// on removing entity from map
	virtual void OnRemoveEnti(EntiSlot* enti) = 0;
	
	/// on adding mine to map (usually at the game start)
	virtual void OnAddMine(Mine* mine) = 0;
	
	/// on removing mine from map
	virtual void OnRemoveMine(Mine* mine) = 0;
	
	/// on holding resources change
	virtual void OnChangeResources(Resources* newResources) = 0;
};
}

#endif    /* _PLAYERSLOT_H */

