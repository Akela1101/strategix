#ifndef _PLAYER_H
#define    _PLAYER_H

#include "Strategix_Forward.h"
#include "MapResource.h"

#include <vector>
#include <string>
#include <set>


namespace Strategix
{
using namespace std;

class Player
{
	friend class FeatureCollect;  // @#~ temporary
	
	PlayerSlot* slot;       // Callback class
	
	const string name;            // Unique name
	const PlayerType type;        // human, ai, net
	const int playerNumber;       // number of player on the map
	
	u_p<Resources> resources;     // available resources amount
	u_p<TechTree> techTree;       // local COPY of race tree
	u_p<MapLocal> map;            // local map for current player
	
	using EntisType = vector<s_p<Enti>>;
	EntisType entis; // owned enties
	
	set<MapResource*> mapResources; // known map resources
	vector<Enti*> entisToRemove; // entis removed at the end of Tick

public:
	Player(string name, PlayerType playerType, int playerNumber, string raceName);
	~Player();
	Player(const Player& orig) = delete;
	Player& operator=(const Player& _c) = delete;
	
	const string& GetName() const { return name; }
	PlayerType GetType() const { return type; }
	int GetPlayerNumber() const { return playerNumber; }
	TechTree& GetTechTree() const { return *techTree; }
	MapLocal& GetMapLocal() const { return *map; }
	
	void SetSlot(PlayerSlot* playerSlot) { this->slot = playerSlot; }
	void Init(u_p<MapLocal> map);
	
	void Tick(float seconds);
	void AddEnti(s_p<Enti> enti);
	void QueueEntiToRemove(Enti* enti);
	void AddMapResource(s_p<MapResource> mapResource);
	void RemoveMapResource(s_p<MapResource> mapResource);
	bool AddResource(const Resource& deltaResource);

private:
	void RemoveEnti(Enti* enti);
};
}

#endif    /* _PLAYER_H */

