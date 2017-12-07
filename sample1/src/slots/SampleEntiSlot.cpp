#include "SampleEntiSlot.h"


namespace sample1
{
SampleEntiSlot::SampleEntiSlot(Enti* enti)
		: EntiSlot(enti)
{
}

void SampleEntiSlot::OnMove(RealCoord coord)
{
	info_raw << "to %.2f, %.2f"s % coord.x % coord.y;
}

}
