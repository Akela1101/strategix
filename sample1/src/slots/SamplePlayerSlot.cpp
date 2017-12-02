#include <slots/SampleEntiSlot.h>

#include "SamplePlayerSlot.h"


namespace sample1
{
using namespace std;
using namespace strx;

void SamplePlayerSlot::EntiAdded(Enti* enti)
{
	auto entiSlot = new SampleEntiSlot(enti);
	entiSlots.emplace_back(entiSlot);
}

}