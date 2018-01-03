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

	//if (auto f = entity->Do<FeatureMove>()) f->Move(coord, 0, nullptr);
}

void EntitySlot::Collect(MapCoord coord, const string& resourceName)
{
//	Client::connect(DoCollect, [entity] (MapCoord coord, const string& resourceName)
//	{
//		if (auto f = entity->Do<FeatureCollect>()) f->Collect(coord, resourceName);
//	});
}

}
