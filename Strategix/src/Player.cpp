/* 
 * File:   Player.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 17:56
 */

#include "Kernel.h"
#include "Enti.h"
#include "TechTree.h"
#include "StrategixSingleton.h"

#include "Player.h"

using namespace Strategix;


Player::Player(string name, PlayerType playerType, int playerNumber, string raceName)
	:
	name(name),
	playerType(playerType),
	playerNumber(playerNumber),
	techTree(new TechTree(*Kernel::GS().techTrees[raceName]))
{	
}

Player::~Player()
{
}

void Player::Tick(const float seconds)
{
}