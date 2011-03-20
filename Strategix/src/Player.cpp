/* 
 * File:   Player.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 17:56
 */

#include "Mediator.h"
#include "KernelBase.h"
#include "Enti.h"
#include "TechTree.h"

#include "Player.h"


namespace Strategix
{

Player::Player(string name, PlayerType playerType, int playerNumber, string raceName)
	:
	name(name),
	playerType(playerType),
	playerNumber(playerNumber),
	techTree(new TechTree(*KernelBase::GS().techTrees[raceName]))
{	
}

Player::~Player()
{
}

void Player::Tick(const float seconds)
{
}

void Player::AddEnti(sh_p<Enti> enti)
{
	entis.push_back(enti);
	enti->player = this;
	mediator->OnAddEnti(enti.get());
}

}
