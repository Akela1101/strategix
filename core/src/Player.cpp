#include "Enti.h"
#include "EntiInfo.h"
#include "MapLocal.h"
#include "PlayerSlot.h"

#include "Player.h"


namespace Strategix
{

Player::Player(const string name, const PlayerType playerType, const int playerNumber, const string raceName)
		: playerSlot(0)
		, name(name)
		, playerType(playerType)
		, playerNumber(playerNumber)
		, resources(KernelBase::GS().MakeResources())
		, techTree(KernelBase::GS().MakeTechTreeCopy(raceName)) {}

void Player::Start()
{
	// Creating Base
	const string baseName = techTree->mainBuildingName;
	s_p<const EntiInfo> entiInfo = techTree->Node(baseName);
	AddEnti(s_p<Enti>(new Enti(entiInfo.get(), mapLocal->GetInitialPostion())));
	
	// @#~ there's still no warfog, so inform each player about resource
	// Resources
	for (int i = 0; i < mapLocal->GetWidth(); ++i)
	{
		for (int j = 0; j < mapLocal->GetLength(); ++j)
		{
			s_p<MapResource> mapResource = mapLocal->GetCell(i, j).mapResource;
			if (mapResource)
			{
				AddMapResource(mapResource);
			}
		}
	}
}

void Player::Tick(const float seconds)
{
	for (auto&& enti : entis)
	{
		enti->Tick(seconds);
	}
	
	// Remove queued entis if there are ones
	if (!entisToRemove.empty())
	{
		for (auto it = entisToRemove.rbegin(); it != entisToRemove.rend(); ++it)
		{
			RemoveEnti(*it);
		}
		entisToRemove.clear();
	}
}

void Player::AddEnti(s_p<Enti> enti)
{
	entis.push_back(enti);
	enti->player = this;
	playerSlot->OnAddEnti(enti);
}

void Player::QueueEntiToRemove(Enti* enti)
{
	entisToRemove.push_back(enti);
}

void Player::RemoveEnti(Enti* enti)
{
	auto itEnti = entis.begin();
	for (; itEnti != entis.end(); ++itEnti) // @#~ Another way - w_p desu.
	{
		if ((*itEnti).get() == enti) // @#~ Also it was possible to check deadness )
		{
			playerSlot->OnRemoveEnti(*itEnti);
			entis.erase(itEnti);
			return;
		}
	}
}

void Player::AddMapResource(s_p<MapResource> mapResource)
{
	mapResources.insert(mapResource.get());
	playerSlot->OnAddMapResource(mapResource);
}

void Player::RemoveMapResource(s_p<MapResource> mapResource)
{
	playerSlot->OnRemoveMapResource(mapResource);
	mapResources.erase(mapResource.get());
}

bool Player::AddResource(const Resource deltaResource)
{
	// @#~ Check it
	
	*resources += deltaResource;
	playerSlot->OnChangeResources(resources);
	return true;
}

}
