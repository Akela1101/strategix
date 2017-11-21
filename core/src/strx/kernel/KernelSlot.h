#ifndef _KERNELSLOT_H
#define _KERNELSLOT_H

#include <nya/signal.hpp>
#include <strx/common/Strategix_Forward.h>


namespace strx
{
class KernelSlot
{
	const string configPath;
	const string mapsPath;
	
public:
	KernelSlot(string configPath, string mapsPath);
	virtual ~KernelSlot() = default;
	
	string GetConfigPath() const { return configPath; }
	string GetMapsPath() const { return mapsPath; }
};

}
#endif