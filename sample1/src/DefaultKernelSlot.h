#ifndef _DEFAULTKERNELSLOT_H
#define    _DEFAULTKERNELSLOT_H

#include <KernelSlot.h>
#include <Sample1_Forward.h>
#include <unordered_map>

namespace Sample1
{
using namespace Strategix;

class DefaultKernelSlot : public KernelSlot
{
	umap<string, u_p<DefaultPlayerSlot>> playerSlots;

public:
	~DefaultKernelSlot() override;
	void OnAddPlayer(Player* player) override;
};

}

#endif    /* _DEFAULTKERNELSLOT_H */

