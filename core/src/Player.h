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
	friend class FeatureCollect; // @#~ temporary

public:
	PlayerSlot* playerSlot; // Callback class
	
	string name; // Name given by user.
	PlayerType playerType; // human, ai, net
	const int playerNumber; // number of player on the map
	
	s_p<Resources> resources;
	s_p<TechTree> techTree; // local COPY of race tree
	s_p<MapLocal> mapLocal;

private:
	typedef vector<s_p<Enti>> EntisType;
	EntisType entis; // owned enties
	
	set<MapResource*> mapResources; // known map resources
	vector<Enti*> entisToRemove; // entis removed at the end of Tick

public:
	Player(string name, PlayerType playerType, int playerNumber, string raceName);
	
	void Start();
	void Tick(float seconds);
	void AddEnti(s_p<Enti> enti);
	void QueueEntiToRemove(Enti* enti);
	void AddMapResource(s_p<MapResource> mapResource);
	void RemoveMapResource(s_p<MapResource> mapResource);
	bool AddResource(const Resource& deltaResource);

private:
	Player(const Player& orig);
	Player& operator=(const Player& _c);
	
	void RemoveEnti(Enti* enti);
};
}

#endif    /* _PLAYER_H */

