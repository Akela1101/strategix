#include <strx/entity/Entity.h>
#include <strx/common/EntityInfo.h>
#include <strx/entity/EntitySlot.h>
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
		, techTree(Kernel::GetTechTree(raceName)) {}

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
			auto entityObject = dynamic_cast<MapEntity*>(object);
			if (entityObject && entityObject->owner == id)
			{
				int objectId = entityObject->id;
				auto& entiName = entityObject->name;
				auto& entiInfo = techTree.GetNode(entiName);
				
				AddEnti(new Entity(entiInfo, objectId, MapCoord(x, y), this));
			}
		}
	}
}

void Player::Tick(float seconds)
{
	for (auto&& entity : entities)
	{
		entity->Tick(seconds);
	}
	
	// Remove queued entities if there are ones
	if (!entisToRemove.empty())
	{
		for (auto it = entisToRemove.rbegin(); it != entisToRemove.rend(); ++it)
		{
			// @#~
		}
		entisToRemove.clear();
	}
}

void Player::AddEnti(Entity* entity)
{
	entities.emplace_back(entity);
	
	slot->EntiAdded(entity);
}

void Player::RemoveEnti(Entity* entity)
{
	entisToRemove.push_back(entity);
}

void Player::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	slot->ResourcesChanged(*resources);
}

Entity* Player::FindCollector(MapCoord coord)
{
	// @#~ Check if there is path to Collector and also select nearest
	// @#~ Check out the case when there are no collectors or more than one
	
	for (auto&& entity : entities)
	{
		if (entity->GetInfo().kind == "building") // @#~ should be building type check
		{
			return entity.get();
		}
	}
	return nullptr;
}

}
