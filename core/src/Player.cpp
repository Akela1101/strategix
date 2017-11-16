#include "Enti.h"
#include "EntiInfo.h"
#include "EntiSlot.h"
#include "Kernel.h"
#include "MapLocal.h"
#include "PlayerSlot.h"
#include "TechTree.h"

#include "Player.h"

#include <utility>


namespace strategix
{

Player::Player(PlayerSlot* slot)
		: slot(slot)
		, resources(Kernel::MakeResources())
		, techTree(Kernel::GetTechTree(slot->GetRaceName())) {}

Player::~Player() = default;

void Player::Init(u_p<MapLocal> mapLocal1)
{
	this->map = move(mapLocal1);
	
	// available resources
	AddResource(*Kernel::MakeResource("gold", 1000));
	
	// resources on map
	for (int i = 0; i < map->GetWidth(); ++i)
	{
		for (int j = 0; j < map->GetLength(); ++j)
		{
			if (s_p<Mine> mine = map->GetCell(i, j).mine)
			{
				AddMine(mine.get()); //TODO: pass without s_p
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
			//RemoveEnti(*it);
		}
		entisToRemove.clear();
	}
}

void Player::AddEnti(EntiSlot* entiSlot)
{
	const string& entiName = entiSlot->GetName();
	auto&& entiInfo = techTree.GetNode(entiName);
	auto enti = make_s<Enti>(entiInfo, map->GetInitialPostion());
	
	entis.push_back(enti); //TODO: pos ?
	enti->player = this;
	
	slot->OnAddEnti(entiSlot);
}

void Player::QueueEntiToRemove(Enti* enti)
{
	entisToRemove.push_back(enti);
}

void Player::AddMine(Mine* mine)
{
	mines.insert(mine);
	slot->OnAddMine(mine);
}

void Player::RemoveMine(Mine* mine)
{
	slot->OnRemoveMine(mine);
	mines.erase(mine);
}

bool Player::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	return true;
}

}
