/* 
 * File:   Player.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 17:56
 */

#ifndef _PLAYER_H
#define	_PLAYER_H

#include "GameStructs.h"
#include "TechTree.h"
#include "GameStructs.h"
#include "Ent.h"

#include "list"

namespace Strategix
{
	using namespace std;

	class Player
	{
	public:
		string name; // Name gived by user.
		PlayerType playerType; // human, ai, net
		const int playerNumber; // number of player on the map

		ResType res;
		TechTree *techTree;
		list<Ent> entities;

	public:
		Player(string name, PlayerType playerType, int playerNumber, string raceName);
		virtual ~Player();
	private:
		Player(const Player& orig);

	};
}

#endif	/* _PLAYER_H */

