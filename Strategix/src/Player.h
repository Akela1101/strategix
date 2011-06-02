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

#include "Strategix_Forward.h"


namespace Strategix
{
	using namespace std;

	class Player
	{
	public:
		PlayerSlot *mediator; // Callback class

		string name; // Name given by user.
		PlayerType playerType; // human, ai, net
		const int playerNumber; // number of player on the map
		Resources resources;
		
		sh_p<TechTree> techTree; // local COPY of race tree
		sh_p<MapLocal> mapLocal;

		typedef	multimap<string, sh_p<Enti> > EntisType;
		EntisType entis;

	public:
		Player(const string name, const PlayerType playerType,
				const int playerNumber, const string raceName);
		
		void Tick(const float seconds);
		void AddEnti(sh_p<Enti> enti);
		bool AddResources(const Resources deltaResources);

	private:
		Player(const Player& orig);
		Player& operator =(const Player &_c);
	};
}

#endif	/* _PLAYER_H */

