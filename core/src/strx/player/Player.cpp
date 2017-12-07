#include <strx/entity/Enti.h>
#include <strx/entity/EntiInfo.h>
#include <strx/entity/EntiSlot.h>
#include <strx/kernel/Kernel.h>
#include <strx/map/Map.h>
#include <strx/map/MapObject.h>
#include <strx/player/PlayerSlot.h>
#include <strx/common/TechTree.h>

#include "Player.h"


namespace strx
{

Player::Player(const string& name, PlayerType type, int id, const string& raceName, u_p<Map> map)
		: name(name)
		, type(type)
		, id(id)
		, raceName(raceName)
		, map(move(map))
		, resources(Kernel::MakeResources())
		, techTree(Kernel::GetTechTree(raceName))
{
	// available resources
	AddResource(*Kernel::MakeResource("gold", 1000));
}

Player::~Player() = default;

void Player::SetSlot(PlayerSlot* slot)
{
	this->slot = slot;
}

void Player::Start()
{
	for (int y : boost::irange(0, map->GetLength()))
	{
		for (int x : boost::irange(0, map->GetWidth()))
		{
			auto object = map->GetCell(x, y).object.get();
			auto playerObject = dynamic_cast<EntityObject*>(object);
			if (playerObject && playerObject->owner == id)
			{
				int objectId = playerObject->id;
				auto& entiName = playerObject->name;
				auto& entiInfo = techTree.GetNode(entiName);
				
				AddEnti(new Enti(entiInfo, objectId, MapCoord(x, y), this));
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
			// @#~
		}
		entisToRemove.clear();
	}
}

void Player::AddEnti(Enti* enti)
{
	entis.emplace_back(enti);
	
	slot->EntiAdded(enti);
}

void Player::RemoveEnti(Enti* enti)
{
	entisToRemove.push_back(enti);
}

bool Player::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	return true;
}

}
