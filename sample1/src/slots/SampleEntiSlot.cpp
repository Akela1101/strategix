#include <strx/entity/Entity.h>

#include "SampleEntiSlot.h"


namespace sample1
{
SampleEntiSlot::SampleEntiSlot(Entity* entity)
		: EntitySlot(entity)
{
}

void SampleEntiSlot::OnMove(RealCoord coord)
{
	emit DoEntityMoved(entity->GetId(), coord);
}

}
