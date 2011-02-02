/* 
 * File:   Game.cpp
 * Author: Akela1101
 * 
 * Created on 10 Январь 2011 г., 10:09
 */

#include "Game.h"


using namespace Strategix;

void Game::Start(string mapName, vector<sh_p<Player> > players)
{
	map.reset(new Map(mapName));
	this->players = players;
}
