#include <slots/SampleEntiSlot.h>

#include "SamplePlayerSlot.h"


namespace sample1
{
using namespace std;
using namespace strx;

void SamplePlayerSlot::AddEnti(SampleEntiSlot* enti)
{
	PlayerSlot::AddEnti(enti);
	entiSlots.emplace_back(enti);
}

}