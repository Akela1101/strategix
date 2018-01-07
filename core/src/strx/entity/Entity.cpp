#include <boost/core/demangle.hpp>
#include <strx/common/EntityInfo.h>
#include <strx/feature/FeatureMove.h>
#include <strx/feature/FeatureCollect.h>
#include <strx/feature/FeatureHealth.h>
#include <strx/feature/FeatureAttack.h>
#include <strx/kernel/Kernel.h>
#include <strx/kernel/Message.h>
#include <strx/map/Map.h>
#include <strx/map/MapObject.h>
#include <strx/player/Player.h>

#include "EntitySlot.h"
#include "Entity.h"


namespace strx
{
Entity::Entity(Game& game, Player& player, IdType id, const EntityInfo& entiInfo, RealCoord coord)
        : game(game)
        , player(player)
        , id(id)
        , entiInfo(entiInfo)
        , coord(coord)
        , mapCoord(coord)
        , task(nullptr)
{
	for (auto&& pa : entiInfo.featureInfos)
	{
		AddFeature(pa.first, pa.second.get());
	}
}

Entity::~Entity() = default;

void Entity::ReceiveMessage(s_p<CommandMessage> message)
{
	switch (message->GetType())
	{
	case Message::Type::MOVE:
	{
		const auto& command = sp_cast<MoveMessage>(message);
		Do<FeatureMove>().Move(command->coord, 0, nullptr);
		break;
	}
	case Message::Type::COLLECT:
	{
		const auto& command = sp_cast<CollectMessage>(message);
		Do<FeatureCollect>().Collect(command->coord, command->resourceName);
		break;
	}
	case Message::Type::ATTACK:
	{
		const auto& command = sp_cast<AttackMessage>(message);
		Do<FeatureAttack>().Attack(command->targetId);
		break;
	}
	default:
		const char* t = message->GetType().c_str();
		nya_throw << "Unable to handle message with type: " << (t[0] == '!' ? message->GetType() : t);
	}
}

void Entity::SetCoord(RealCoord coord)
{
	this->coord = coord;
	Kernel::SendMessageAll(make_s<RealMoveMessage>(GetId(), coord));
}

Feature& Entity::GetFeature(type_index type) const
{
	auto iFeature = features.find(type);
	if (iFeature == features.end())
	{
		nya_throw << "%s has no feature %s"s % entiInfo.name % boost::core::demangle(type.name());
	}
	return *iFeature->second.get();
}

void Entity::AddFeature(const string& name, const FeatureInfo* featureInfo)
{
	if (name == "move")
	{
		features[typeid(FeatureMove)].reset(new FeatureMove(featureInfo, this));
	}
	else if (name == "collect")
	{
		features[typeid(FeatureCollect)].reset(new FeatureCollect(featureInfo, this));
	}
	else if (name == "health")
	{
		features[typeid(FeatureHealth)].reset(new FeatureHealth(featureInfo, this));
	}
	else if (name == "attack")
	{
		features[typeid(FeatureAttack)].reset(new FeatureAttack(featureInfo, this));
	}
	else
	{
		error_log << "Unable to handle feature " << name;
	}
}

bool Entity::SetMapCoord(MapCoord newCoord)
{
	if (mapCoord != newCoord)
	{
		auto& currentObject = player.GetMapObject(mapCoord);
		auto& object = player.GetMapObject(newCoord);
		if (object)
		{
			return currentObject == object;
		}
		object = move(currentObject);

		Kernel::SendMessageAll(make_s<MapMoveMessage>(GetId(), mapCoord, newCoord));
		mapCoord = newCoord;
	}
	return true;
}

void Entity::Tick(float seconds)
{
	for (auto&& feature : passiveTasks)
	{
		feature->Tick(seconds);
	}

	if (task) task->Tick(seconds);
}

void Entity::AssignTask(Feature* feature)
{
	if (task) task->Stop();

	task = feature;
}

void Entity::AssignPassiveTask(Feature* feature)
{
	passiveTasks.push_back(feature);
}

}
