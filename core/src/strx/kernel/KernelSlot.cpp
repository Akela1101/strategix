#include <strx/kernel/Kernel.h>

#include "KernelSlot.h"

namespace strx
{

KernelSlot::KernelSlot(std::string configPath, std::string mapsPath)
		: configPath(move(configPath)), mapsPath(move(mapsPath))
{
}

}
