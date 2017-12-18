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
	emit DoMoved(entity->GetId(), coord);
}

void SampleEntiSlot::OnMapMove(MapCoord from, MapCoord to)
{
	emit DoMapMoved(from, to);
}

}
