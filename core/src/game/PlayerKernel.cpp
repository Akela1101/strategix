#include "../../strx/Entity.hpp"
#include "../../strx/EntityInfo.hpp"
#include "../../strx/Kernel.hpp"
#include "../../strx/Map.hpp"
#include "../../strx/MapMine.hpp"
#include "../../strx/MapObject.hpp"
#include "../../strx/Message.hpp"
#include "../../strx/Player.hpp"
#include "../entity/EntityKernel.hpp"
#include "../map/MapPath.hpp"
#include "../map/PathFinder.hpp"

#include "PlayerKernel.hpp"


namespace strx
{

PlayerKernel::PlayerKernel(GameKernel& game, PlayerId id, const PlayerMessage& playerMessage, Map& map)
        : game(game)
        , id(id)
        , type(playerMessage.type)
        , spot(playerMessage.spot)
        , name(playerMessage.name)
        , race(playerMessage.race)
        , map(map)
        , pathFinder(new PathFinder(map))
        , resources(Kernel::MakeResources())
        , techTree(Kernel::GetTechTree(race))
{}

PlayerKernel::~PlayerKernel() = default;

s_p<EntityKernel> PlayerKernel::GetEntity(IdType id) const
{
	auto i = entities.find(id);
	return i == entities.end() ? nullptr : i->second;
}

Terrain* PlayerKernel::GetTerrain(MapCoord coord) const
{
	return map.GetCell(coord).terrain;
}

u_p<MapObject>& PlayerKernel::GetMapObject(MapCoord coord) const
{
	return map.GetCell(coord).object;
}

MapMine* PlayerKernel::GetMine(MapCoord coord) const
{
	return dynamic_cast<MapMine*>(GetMapObject(coord).get());
}

void PlayerKernel::EntityAdded(s_p<EntityKernel> entity)
{
	EntityKernel& entityRef = *entity;
	entities.emplace(entityRef.GetId(), move(entity));
	Kernel::SendMessageAll(make_s<EntityMessage>(spot, entityRef.GetId(), entityRef.GetMaxHp()));
}

void PlayerKernel::EntityRemoved(IdType id)
{
	auto i = entities.find(id);
	MapCoord coord = i->second->GetMapCoord();

	entities.erase(i);
	ObjectRemoved(id, coord);
}

void PlayerKernel::AddResource(const Resource& deltaResource)
{
	*resources += deltaResource;
	if (GetType() == PlayerType::HUMAN) Kernel::SendMessageOne(make_s<ResourcesMessage>(*resources), id);
}

EntityKernel* PlayerKernel::FindCollector(MapCoord coord) const
{
	// @#~ Check if there is path to Collector and also select nearest
	// @#~ Check out the case when there are no collectors or more than one

	for (auto& entity : entities | nya::map_values)
	{
		if (entity->GetInfo().kind == "building")  // @#~ should be building type check
		{
			return entity.get();
		}
	}
	return nullptr;
}

MapMine* PlayerKernel::FindMine(MapCoord coord, string resourceName, int squareRadius) const
{
	if (squareRadius == 0) return GetMine(coord);

	// check concentric squares from smallest to largest
	for (int r : boost::irange(1, squareRadius))
	{
		MapCoord froms[] = {{-r, -r}, {-r + 1, r}, {-r, -r + 1}, {r, -r}};  // h,h,v,v
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
					if (mine && mine->name == resourceName) return mine;
				}
			}
		}
	}
	return nullptr;
}

u_p<MapPath> PlayerKernel::FindPath(MapCoord from, MapCoord till, float radius) const
{
	return pathFinder->FindPath(from, till, radius);
}

ResourceUnit PlayerKernel::PickResource(MapMine* mine, ResourceUnit amount)
{
	ResourceUnit picked = mine->PickResource(amount);
	Kernel::SendMessageAll(make_s<MineAmountMessage>(mine->id, mine->amount));

	if (!mine->amount) ObjectRemoved(mine->id, mine->coord);
	return picked;
}

void PlayerKernel::ObjectRemoved(IdType id, MapCoord coord)
{
	map.ChangeObject(map.GetCell(coord), nullptr);
	Kernel::SendMessageAll(make_s<ObjectRemovedMessage>(id));
}
}  // namespace strx
