/* 
 * File:   Player.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 17:56
 */

#ifndef _PLAYER_H
#define	_PLAYER_H

#include "StrategixCommon.h"

#include <list>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;

	class TechTree;
	class Enti;
	class Mediator;
	class MapLocal;

	class Player
	{
	public:
		Mediator *mediator; // Callback class

		//
		string name; // Name gived by user.
		PlayerType playerType; // human, ai, net
		const int playerNumber; // number of player on the map

		// Resources resources;
		
		sh_p<TechTree> techTree; // local copy of race tree

		list<sh_p<Enti> > entis;
		
		sh_p<MapLocal> map;

	public:
		Player(string name, PlayerType playerType, int playerNumber, string raceName);
		virtual ~Player();

		void Tick(const float seconds);
		void AddEnti(sh_p<Enti> enti);

	private:
		Player(const Player& orig);

	};
}

#endif	/* _PLAYER_H */

