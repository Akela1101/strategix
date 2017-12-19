#include <strx/entity/Entity.h>

#include "SampleEntitySlot.h"


namespace sample1
{
SampleEntitySlot::SampleEntitySlot(Entity* entity)
		: EntitySlot(entity)
{
}

void SampleEntitySlot::OnMove(RealCoord coord)
{
	emit DoMoved(entity->GetId(), coord);
}

}
