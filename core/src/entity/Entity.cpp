#include "../../strx/Game.hpp"
#include "../../strx/Message.hpp"
#include "../../strx/Player.hpp"

#include "../../strx/Entity.hpp"
#include "EntityKernel.hpp"

namespace strx
{

Entity::Entity(s_p<EntityMessage> entityMessage) : entityMessage(move(entityMessage)) {}

IdType Entity::GetId() const
{
	return entityMessage->id;
}

HpType Entity::GetMaxHp() const
{
	return entityMessage->maxHp;
}

void Entity::Move(MapCoord coord)
{
	Game::SendMessageOne(make_s<MoveMessage>(GetId(), coord));
}

void Entity::Collect(MapCoord coord, const string& resourceName)
{
	Game::SendMessageOne(make_s<CollectMessage>(GetId(), coord, resourceName));
}

void Entity::Attack(IdType targetId)
{
	Game::SendMessageOne(make_s<AttackMessage>(GetId(), targetId));
}

}  // namespace strx
