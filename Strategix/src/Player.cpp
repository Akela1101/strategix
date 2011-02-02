/* 
 * File:   Player.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 17:56
 */

#include "Player.h"
#include "StrategixSingleton.h"
#include "Kernel.h"

using namespace Strategix;

Player::Player(string name, PlayerType playerType, int playerNumber, string raceName)
	:
	name(name),
	playerType(playerType),
	playerNumber(playerNumber)
{
	techTree = Kernel::GS().techTrees[raceName].get();
}

Player::~Player()
{
}

