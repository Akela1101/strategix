#include <utility>

#include <strx/entity/Enti.h>
#include <strx/entity/EntiInfo.h>
#include <strx/entity/EntiSlot.h>
#include <strx/kernel/Kernel.h>
#include <strx/map/Map.h>
#include <strx/player/PlayerSlot.h>
#include <strx/common/TechTree.h>

#include "Player.h"


namespace strx
{

Player::Player(PlayerSlot* slot)
		: slot(slot)
		, resources(Kernel::MakeResources())
		, techTree(Kernel::GetTechTree(slot->GetRaceName()))
{
	slot->player = this;
}

Player::~Player() = default;

void Player::Init(u_p<Map> map)
{
	this->map = move(map);
	
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
	auto enti = new Enti(entiInfo, RealCoord(5, 5)); //TODO: coord
	
	entis.emplace_back(enti);
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
