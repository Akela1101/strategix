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
#include "EntiInfo.h"


namespace Strategix
{

Player::Player(string name, PlayerType playerType, int playerNumber, string raceName)
	:
	mediator(0),
	name(name),
	playerType(playerType),
	playerNumber(playerNumber),
	techTree(new TechTree(KernelBase::GS().GetTechTree(raceName)))
{	
}

void Player::Tick(const float seconds)
{
	foreach(const EntisType::value_type &pa, entis)
	{
		pa.second->Tick(seconds);
	}
}

void Player::AddEnti(sh_p<Enti> enti)
{
	entis.insert(EntisType::value_type(enti->entityInfo->name, enti));
	enti->player = this;
	if( mediator )
		mediator->OnAddEnti(enti.get());
}

bool Player::AddResources(const Resources deltaResources)
{
	if( resources.isNegative() )
		return false;

	resources += deltaResources;
	if( mediator )
		mediator->OnChangeResources(resources);

	return true;
}

}
