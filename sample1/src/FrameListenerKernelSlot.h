#ifndef _FRAMELISTENERKERNELSLOT_H
#define    _FRAMELISTENERKERNELSLOT_H

#include <Strategix_Forward.h>
#include "Sample1_Forward.h"


namespace Sample1
{
using namespace Strategix;

class FrameListenerKernelSlot
{
	//s_p<HumanPlayerSlot> humanPlayerSlot;
	s_p<AiPlayerSlot> aiPlayerSlot;

public:
	FrameListenerKernelSlot();
	virtual ~FrameListenerKernelSlot() = default;
};

}

#endif    /* _FRAMELISTENERKERNELSLOT_H */

