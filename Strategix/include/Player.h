/* 
 * File:   Player.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 17:56
 */

#ifndef _PLAYER_H
#define	_PLAYER_H

#include "GameStructs.h"

#include <list>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;

	class Enti;
	class TechTree;

	class Player
	{
	public:
		string name; // Name gived by user.
		PlayerType playerType; // human, ai, net
		const int playerNumber; // number of player on the map

		map<string, ResType> resources;
		sh_p<TechTree> techTree; // local copy of race tree
		list<Enti> entis;

	public:
		Player(string name, PlayerType playerType, int playerNumber, string raceName);
		virtual ~Player();

		void Tick(const float seconds);

	private:
		Player(const Player& orig);

	};
}

#endif	/* _PLAYER_H */

