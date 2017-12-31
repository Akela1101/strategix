#include <strx/feature/FeatureCollect.h>
#include <strx/feature/FeatureMove.h>
#include <strx/network/Client.h>
#include <strx/network/Message.h>

#include "Entity.h"
#include "EntitySlot.h"


namespace strx
{

EntitySlot::EntitySlot(s_p<EntityMessage> entityMessage)
    : entityMessage(move(entityMessage))
{
	//TODO: !!!
//	Client::connect(DoMove, [entity] (MapCoord coord)
//	{
//		if (auto f = entity->Do<FeatureMove>()) f->Move(coord, 0, nullptr);
//	});
//	Client::connect(DoCollect, [entity] (MapCoord coord, const string& resourceName)
//	{
//		if (auto f = entity->Do<FeatureCollect>()) f->Collect(coord, resourceName);
//	});
}

IdType EntitySlot::GetId() const { return entityMessage->id; }

}
