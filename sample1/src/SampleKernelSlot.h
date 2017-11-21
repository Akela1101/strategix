#ifndef _SAMPLEKERNELSLOT_H
#define    _SAMPLEKERNELSLOT_H

#include <strx/kernel/KernelSlot.h>
#include <Sample_Forward.h>

namespace sample1
{
using namespace strx;

class SampleKernelSlot : public KernelSlot
{
	umap<string, u_p<SamplePlayerSlot>> playerSlots;

public:
	SampleKernelSlot(std::string configPath, std::string mapsPath);
	~SampleKernelSlot() override;
};

}

#endif    /* _SAMPLEKERNELSLOT_H */

