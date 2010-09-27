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
#include "Entity.h"

#include "list"

namespace Strategix
{
	using namespace std;

	class Player
	{
		string name;
		Resources resources;
		TechTree *techTree;
		list<Entity> entities;

	public:
		Player();
		Player(const Player& orig);
		virtual ~Player();
	private:

	};
}

#endif	/* _PLAYER_H */

