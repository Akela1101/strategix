#include <strx/entity/Entity.h>
#include <strx/common/EntityInfo.h>
#include <strx/entity/EntitySlot.h>
#include <strx/kernel/Kernel.h>
#include <strx/map/Map.h>
#include <strx/map/MapMine.h>
#include <strx/map/MapObject.h>
#include <strx/map/MapPath.h>
#include <strx/map/PathFinder.h>
#include <strx/player/PlayerSlot.h>
#include <strx/common/TechTree.h>

#include "Player.h"


namespace strx
{

Player::Player(const string& name, PlayerType type, int id, const string& raceName, Map& map)
		: name(name)
		, type(type)
		, id(id)
		, raceName(raceName)
		, map(map)
		, pathFinder(new PathFinder(map))
		, resources(Kernel::MakeResources())
		, techTree(Kernel::GetTechTree(raceName)) {}

Player::~Player() = default;

Terrain* Player::GetTerrain(MapCoord coord) const
{
	return map.GetCell(coord).terrain;
}

u_p<MapObject>& Player::GetMapObject(MapCoord coord) const
{
	return map.GetCell(coord).object;
}

MapMine* Player::GetMine(MapCoord coord, string resourceName) const
{
	auto mine = dynamic_cast<MapMine*>(GetMapObject(coord).get());
	return mine && mine->name == resourceName ? mine : nullptr;
}

void Player::SetSlot(PlayerSlot* slot)
{
	this->slot = slot;
}

void Player::Start()
{
	for (int y : boost::irange(0, map.GetLength()))
	{
		for (int x : boost::irange(0, map.GetWidth()))
		{
			auto object = map.GetCell(x, y).object.get();
			auto entityObject = dynamic_cast<MapEntity*>(object);
			if (entityObject && entityObject->owner == id)
			{
				int objectId = entityObject->id;
				auto& name = entityObject->name;
				auto& info = techTree.GetNode(name);
				
				AddEntity(new Entity(info, objectId, MapCoord(x, y), this));
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

void Player::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);
	
	slot->EntiAdded(entity);
}

void Player::RemoveEntity(Entity* entity)
{
	entisToRemove.push_back(entity);
}

void Player::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	slot->ResourcesChanged(*resources);
}

Entity* Player::FindCollector(MapCoord coord) const
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

MapMine* Player::FindMine(MapCoord coord, string resourceName, float radius) const
{
	if (radius == 0) GetMine(coord, resourceName);
	
	return nullptr;
}

u_p<MapPath> Player::FindPath(MapCoord from, MapCoord till, float radius) const
{
	return pathFinder->FindPath(from, till, radius);
}

ResourceUnit Player::PickResource(MapMine* mine, ResourceUnit amount)
{
	ResourceUnit picked = mine->PickResource(amount);
	slot->MineAmountChanged(mine->id, mine->amount);
	
	if (!mine->amount)
	{
		// remove empty mine
		IdType mineId = mine->id;
		map.ChangeObject(map.GetCell(mine->coord), nullptr);
		slot->MineRemoved(mineId);
	}
	return picked;
}
}
