#include <strx/feature/FeatureCollect.h>
#include <strx/feature/FeatureMove.h>
#include <strx/game/GameSlot.h>
#include <strx/kernel/Message.h>

#include "Entity.h"
#include "EntitySlot.h"


namespace strx
{

EntitySlot::EntitySlot(s_p<EntityMessage> entityMessage)
    : entityMessage(move(entityMessage))
{}

IdType EntitySlot::GetId() const
{
	return entityMessage->id;
}

void EntitySlot::Move(MapCoord coord)
{
	GameSlot::SendMessageOne(make_s<MoveMessage>(GetId(), coord));
}

void EntitySlot::Collect(MapCoord coord, const string& resourceName)
{
	GameSlot::SendMessageOne(make_s<CollectMessage>(GetId(), coord, resourceName));
}

}
