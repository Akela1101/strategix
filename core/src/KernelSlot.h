#ifndef _KERNELSLOT_H
#define _KERNELSLOT_H

#include <Strategix_Forward.h>

namespace Strategix
{
class KernelSlot
{
public:
	virtual ~KernelSlot() = default;
	virtual void OnAddPlayer(Player* player) = 0;
};

}
#endif