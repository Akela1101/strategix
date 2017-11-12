#include "Enti.h"
#include "EntiInfo.h"
#include "Kernel.h"
#include "MapLocal.h"
#include "PlayerSlot.h"
#include "TechTree.h"

#include "Player.h"

#include <utility>


namespace Strategix
{

Player::Player(string name, PlayerType playerType, int playerNumber, string raceName)
		: slot(nullptr)
		, name(move(name))
		, type(playerType)
		, playerNumber(playerNumber)
		, resources(Kernel::MakeResources())
		, techTree(Kernel::MakeTechTreeCopy(raceName)) {}

Player::~Player() = default;

void Player::Init(u_p<MapLocal> mapLocal1)
{
	this->map = move(mapLocal1);
	
	// headquarters
	const string& headquartersName = techTree->mainBuildingName;
	auto&& headquartersInfo = techTree->Node(headquartersName);
	MapCoord hqCoord = map->GetInitialPostion();
	AddEnti(make_s<Enti>(*headquartersInfo, hqCoord));
	
	// some workers
	auto&& workerInfo = *GetTechTree().Node("Spher_Worker");
	AddEnti(make_s<Enti>(workerInfo, hqCoord + MapCoord(2, 0)));
	AddEnti(make_s<Enti>(workerInfo, hqCoord + MapCoord(0, 2)));
	
	// available resources
	AddResource(*Kernel::MakeResource("gold", 1000));
	
	// resources on map
	for (int i = 0; i < map->GetWidth(); ++i)
	{
		for (int j = 0; j < map->GetLength(); ++j)
		{
			if (s_p<MapResource> mapResource = map->GetCell(i, j).mapResource)
			{
				AddMapResource(mapResource);
			}
		}
	}
}

void Player::Tick(float seconds)
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
	
	if (slot) slot->OnAddEnti(enti);
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
			slot->OnRemoveEnti(*itEnti);
			entis.erase(itEnti);
			return;
		}
	}
}

void Player::AddMapResource(s_p<MapResource> mapResource)
{
	mapResources.insert(mapResource.get());
	if (slot) slot->OnAddMapResource(mapResource);
}

void Player::RemoveMapResource(s_p<MapResource> mapResource)
{
	slot->OnRemoveMapResource(mapResource);
	mapResources.erase(mapResource.get());
}

bool Player::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	return true;
}

}
