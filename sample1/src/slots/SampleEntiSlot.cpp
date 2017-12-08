#include <strx/entity/Enti.h>

#include "SampleEntiSlot.h"


namespace sample1
{
SampleEntiSlot::SampleEntiSlot(Enti* enti)
		: EntiSlot(enti)
{
}

void SampleEntiSlot::OnMove(RealCoord coord)
{
	emit DoEntityMoved(enti->GetId(), coord);
}

}
