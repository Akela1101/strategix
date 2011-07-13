/* 
 * File:   Player.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 17:56
 */

#include "Enti.h"
#include "EntiInfo.h"
#include "KernelBase.h"
#include "MapLocal.h"
#include "PlayerSlot.h"
#include "TechTree.h"

#include "Player.h"


namespace Strategix
{

Player::Player(const string name, const PlayerType playerType,
				const int playerNumber, const string raceName)
	:
	playerSlot(0),
	name(name),
	playerType(playerType),
	playerNumber(playerNumber),
	resources(KernelBase::GS().MakeResources()),
	techTree(KernelBase::GS().MakeTechTreeCopy(raceName))
{}

void Player::Start()
{
	// Creating Base
	const string baseName = techTree->mainBuildingName;
	sh_p<const EntiInfo> entityInfo = techTree->Node(baseName);
	AddEnti(sh_p<Enti>(new Enti(entityInfo.get(), mapLocal->GetInitialPostion())));

	// @#~ there's still no warfog, so inform each player about resource
	// Resources
	for( int i = 0; i < mapLocal->GetWidth(); ++i )
	{
		for( int j = 0; j < mapLocal->GetLength(); ++j )
		{
			sh_p<MapResource> mapResource = mapLocal->GetCell(i, j).mapResource;
			if( mapResource )
			{
				AddMapResource(mapResource);
			}
		}
	}
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
	if( playerSlot )
		playerSlot->OnAddEnti(enti);
}

void Player::AddMapResource(sh_p<MapResource> mapResource)
{
	mapResources.insert(mapResource.get());
	if( playerSlot )
		playerSlot->OnAddMapResource(mapResource);
}

bool Player::AddResource(const Resource deltaResource)
{
	// @#~ Check it
	
	*resources += deltaResource;
	if( playerSlot )
		playerSlot->OnChangeResources(resources);
	return true;
}

}
