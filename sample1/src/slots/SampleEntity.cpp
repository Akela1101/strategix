#include <strx/entity/Entity.h>

#include "SampleEntity.h"


namespace sample1
{
SampleEntity::SampleEntity(Entity* entity)
		: EntitySlot(entity)
{
}

void SampleEntity::OnMove(RealCoord coord)
{
	emit DoMoved(entity->GetId(), coord);
}

}
