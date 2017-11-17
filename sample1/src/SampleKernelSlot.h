#ifndef _SAMPLEKERNELSLOT_H
#define    _SAMPLEKERNELSLOT_H

#include <KernelSlot.h>
#include <Sample1_Forward.h>
#include <unordered_map>

namespace sample1
{
using namespace strategix;

class SampleKernelSlot : public KernelSlot
{
	umap<string, u_p<SamplePlayerSlot>> playerSlots;

public:
	using KernelSlot::KernelSlot;
	~SampleKernelSlot() override;
};

}

#endif    /* _SAMPLEKERNELSLOT_H */

