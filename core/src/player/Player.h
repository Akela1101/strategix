#ifndef _PLAYER_H
#define    _PLAYER_H

#include <map/Mine.h>
#include <player/PlayerSlot.h>
#include <Strategix_Forward.h>

#include <vector>
#include <string>
#include <set>


namespace strategix
{
using namespace std;

class Player
{
	friend class FeatureCollect;  // @#~ temporary
	
	u_p<PlayerSlot> slot;         // Callback class
	u_p<Resources> resources;     // available resources amount
	u_p<MapLocal> map;            // local map for current player
	const TechTree& techTree;     // link to tech tree
	
	using EntisType = vector<s_p<Enti>>;
	EntisType entis; // owned enties
	
	set<Mine*> mines; // known map resources
	vector<Enti*> entisToRemove; // entis removed at the end of Tick

public:
	Player(PlayerSlot* slot);
	~Player();
	Player(const Player& orig) = delete;
	Player& operator=(const Player& _c) = delete;
	
	const string& GetName() const { return slot->GetName(); }
	PlayerType GetType() const { return slot->GetType(); }
	int GetPlayerNumber() const { return slot->GetPlayerNumber(); }
	MapLocal& GetMapLocal() const { return *map; }
	const TechTree& GetTechTree() const { return techTree; }
	
	void Init(u_p<MapLocal> map);
	void Tick(float seconds);
	void AddEnti(EntiSlot* entiSlot);
	void QueueEntiToRemove(Enti* enti);
	void AddMine(Mine* mine);
	void RemoveMine(Mine* mine);
	bool AddResource(const Resource& deltaResource);
};
}

#endif    /* _PLAYER_H */

