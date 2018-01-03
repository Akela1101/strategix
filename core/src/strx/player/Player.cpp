#include <strx/entity/Entity.h>
#include <strx/common/EntityInfo.h>
#include <strx/entity/EntitySlot.h>
#include <strx/kernel/Kernel.h>
#include <strx/map/Map.h>
#include <strx/map/MapMine.h>
#include <strx/map/MapObject.h>
#include <strx/map/MapPath.h>
#include <strx/map/PathFinder.h>
#include <strx/kernel/Message.h>
#include <strx/player/PlayerSlot.h>
#include <strx/common/TechTree.h>

#include "Player.h"


namespace strx
{

Player::Player(const PlayerMessage& playerMessage, PlayerId playerId, Map& map)
        : playerId(playerId)
        , type(playerMessage.type)
        , spot(playerMessage.spot)
        , name(playerMessage.name)
        , race(playerMessage.race)
        , map(map)
        , pathFinder(new PathFinder(map))
        , resources(Kernel::MakeResources())
        , techTree(Kernel::GetTechTree(race)) {}

Player::~Player() = default;

Terrain* Player::GetTerrain(MapCoord coord) const
{
	return map.GetCell(coord).terrain;
}

u_p<MapObject>& Player::GetMapObject(MapCoord coord) const
{
	return map.GetCell(coord).object;
}

MapMine* Player::GetMine(MapCoord coord) const
{
	return dynamic_cast<MapMine*>(GetMapObject(coord).get());
}

void Player::Start()
{
	for (int y : boost::irange(0, map.GetLength()))
	{
		for (int x : boost::irange(0, map.GetWidth()))
		{
			auto object = map.GetCell(x, y).object.get();
			auto entityObject = dynamic_cast<MapEntity*>(object);
			if (entityObject && entityObject->owner == spot)
			{
				int objectId = entityObject->id;
				auto& name = entityObject->name;
				auto& info = techTree.GetNode(name);

				AddEntity(make_u<Entity>(info, objectId, MapCoord(x, y), this));
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

void Player::AddEntity(u_p<Entity> entity)
{
	Kernel::SendMessageOne(make_s<EntityMessage>(spot, entity->GetId()), playerId);
	entities.push_back(move(entity));
}

void Player::RemoveEntity(Entity* entity)
{
	entisToRemove.push_back(entity);
}

void Player::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	//*resources
	Kernel::SendMessageOne(make_s<ResourcesMessage>(), playerId);
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

MapMine* Player::FindMine(MapCoord coord, string resourceName, int squareRadius) const
{
	if (squareRadius == 0) return GetMine(coord);

	// check concentric squares from smallest to largest
	for (int r : boost::irange(1, squareRadius))
	{
		MapCoord froms[] = { { -r, -r }, { -r + 1, r }, { -r, -r + 1 }, { r, -r } }; // h,h,v,v
		for (int i : boost::irange(0, 4))
		{
			MapCoord from = coord + froms[i];
			int& d = i < 2 ? from.x : from.y;
			int dEnd = d + 2 * r;
			for (; d < dEnd; ++d)
			{
				if (map.IsCell(from))
				{
					auto mine = dynamic_cast<MapMine*>(map.GetCell(from).object.get());
					if (mine && mine->name == resourceName)
					{
						return mine;
					}
				}
			}
		}
	}
	return nullptr;
}

u_p<MapPath> Player::FindPath(MapCoord from, MapCoord till, float radius) const
{
	return pathFinder->FindPath(from, till, radius);
}

ResourceUnit Player::PickResource(MapMine* mine, ResourceUnit amount)
{
	ResourceUnit picked = mine->PickResource(amount);
	//slot->MineAmountChanged(mine->id, mine->amount);
	Kernel::SendMessageOne(s_p<MineMessage>(), playerId);

	if (!mine->amount)
	{
		// remove empty mine
		IdType mineId = mine->id;
		map.ChangeObject(map.GetCell(mine->coord), nullptr);
		Kernel::SendMessageOne(make_s<MineRemovedMessage>(), playerId);//mineId
	}
	return picked;
}
}
