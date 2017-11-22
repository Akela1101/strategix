#include <slots/SamplePlayerSlot.h>

#include "SampleKernelSlot.h"


namespace sample1
{
using namespace strx;

SampleKernelSlot::SampleKernelSlot(std::string configPath, std::string mapsPath)
		: KernelSlot(move(configPath), move(mapsPath)) {}

SampleKernelSlot::~SampleKernelSlot() = default;

}
