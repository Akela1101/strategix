/* 
 * File:   Player.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 17:56
 */

#ifndef _PLAYER_H
#define	_PLAYER_H

#include <map>
#include <string>
#include <set>

#include "Strategix_Forward.h"
#include "MapResource.h"


namespace Strategix
{
	using namespace std;

	class Player
	{
		friend class FeatureCollect; // @#~ temporary

	public:
		PlayerSlot *playerSlot; // Callback class

		string name; // Name given by user.
		PlayerType playerType; // human, ai, net
		const int playerNumber; // number of player on the map
		Resources resources;
		
		sh_p<TechTree> techTree; // local COPY of race tree
		sh_p<MapLocal> mapLocal;

	private:
		typedef	multimap<string, sh_p<Enti> > EntisType;
		EntisType entis; // owned enties

		set<MapResource*> mapResources; // known map resources

	public:
		Player(const string name, const PlayerType playerType,
				const int playerNumber, const string raceName);

		void Start();
		void Tick(const float seconds);
		void AddEnti(sh_p<Enti> enti);
		void AddMapResource(sh_p<MapResource> mapResource);
		bool AddResources(const Resources deltaResources);

	private:
		Player(const Player& orig);
		Player& operator =(const Player &_c);
	};
}

#endif	/* _PLAYER_H */

