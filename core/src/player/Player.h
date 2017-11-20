#ifndef _PLAYER_H
#define    _PLAYER_H

#include <vector>
#include <unordered_set>

#include <map/Mine.h>
#include <player/PlayerSlot.h>
#include <common/Strategix_Forward.h>


namespace strategix
{

class Player
{
	friend class FeatureCollect;  // @#~ temporary
	
	u_p<PlayerSlot> slot;         // Callback class
	u_p<Resources> resources;     // available resources amount
	u_p<Map> map;                 // local map for current player
	const TechTree& techTree;     // link to tech tree
	
	using EntisType = vector<s_p<Enti>>;
	EntisType entis; // owned enties
	
	vector<Enti*> entisToRemove; // entis removed at the end of Tick

public:
	Player(PlayerSlot* slot);
	~Player();
	Player(const Player& orig) = delete;
	Player& operator=(const Player& _c) = delete;
	
	const string& GetName() const { return slot->GetName(); }
	PlayerType GetType() const { return slot->GetType(); }
	int GetId() const { return slot->GetId(); }
	Map& GetMap() const { return *map; }
	const TechTree& GetTechTree() const { return techTree; }
	
	void Init(u_p<Map> map);
	void Tick(float seconds);
	void AddEnti(EntiSlot* entiSlot);
	void QueueEntiToRemove(Enti* enti);
	void AddMine(Mine* mine);
	void RemoveMine(Mine* mine);
	bool AddResource(const Resource& deltaResource);
};
}

#endif    /* _PLAYER_H */

