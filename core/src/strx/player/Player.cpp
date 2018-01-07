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

#include "Player.h"


namespace strx
{

Player::Player(Game& game, PlayerId id, const PlayerMessage& playerMessage, Map& map)
        : game(game)
        , id(id)
        , type(playerMessage.type)
        , spot(playerMessage.spot)
        , name(playerMessage.name)
        , race(playerMessage.race)
        , map(map)
        , pathFinder(new PathFinder(map))
        , resources(Kernel::MakeResources())
        , techTree(Kernel::GetTechTree(race)) {}

Player::~Player() = default;

s_p<Entity> Player::GetEntity(IdType id) const
{
	auto i = entities.find(id);
	return i == entities.end() ? nullptr : i->second;
}

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

void Player::EntityAdded(s_p<Entity> entity)
{
	Entity& entityRef = *entity;
	entities.emplace(entityRef.GetId(), move(entity));
	Kernel::SendMessageAll(make_s<EntityMessage>(spot, entityRef.GetId()));
}

void Player::EntityRemoved(IdType id)
{
	auto i = entities.find(id);
	MapCoord coord = i->second->GetMapCoord();

	entities.erase(i);
	ObjectRemoved(id, coord);
}

void Player::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	if (GetType() == PlayerType::HUMAN)
	{
		Kernel::SendMessageOne(make_s<ResourcesMessage>(*resources), id);
	}
}

Entity* Player::FindCollector(MapCoord coord) const
{
	// @#~ Check if there is path to Collector and also select nearest
	// @#~ Check out the case when there are no collectors or more than one

	for (auto& entity : entities | nya::map_values)
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
	Kernel::SendMessageAll(make_s<MineAmountMessage>(mine->id, mine->amount));

	if (!mine->amount) ObjectRemoved(mine->id, mine->coord);
	return picked;
}

void Player::ObjectRemoved(IdType id, MapCoord coord)
{
	map.ChangeObject(map.GetCell(coord), nullptr);
	Kernel::SendMessageAll(make_s<ObjectRemovedMessage>(id));
}
}
