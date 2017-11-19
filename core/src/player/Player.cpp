#include <utility>

#include <entity/Enti.h>
#include <entity/EntiInfo.h>
#include <entity/EntiSlot.h>
#include <Kernel.h>
#include <map/Map.h>
#include <player/PlayerSlot.h>
#include <common/TechTree.h>

#include "Player.h"


namespace strategix
{

Player::Player(PlayerSlot* slot)
		: slot(slot)
		, resources(Kernel::MakeResources())
		, techTree(Kernel::GetTechTree(slot->GetRaceName())) {}

Player::~Player() = default;

void Player::Init(u_p<Map> mapLocal1)
{
	this->map = move(mapLocal1);
	
	// available resources
	AddResource(*Kernel::MakeResource("gold", 1000));
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
	auto enti = make_s<Enti>(entiInfo, MapCoord()); //TODO: pos ?
	
	entis.push_back(enti);
	enti->player = this;
	
	slot->OnAddEnti(entiSlot);
}

void Player::QueueEntiToRemove(Enti* enti)
{
	entisToRemove.push_back(enti);
}

void Player::AddMine(Mine* mine)
{
	slot->OnAddMine(mine);
}

void Player::RemoveMine(Mine* mine)
{
	slot->OnRemoveMine(mine);
}

bool Player::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	return true;
}

}
