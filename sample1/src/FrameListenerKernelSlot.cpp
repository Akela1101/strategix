#include "AiPlayerSlot.h"

#include "../../core/src/Strategix.h"

#include "FrameListenerKernelSlot.h"


namespace Sample1
{
using namespace Strategix;

FrameListenerKernelSlot::FrameListenerKernelSlot(s_p<Kernel> kernel)
		: kernel(kernel)
{
	// humanPlayerSlot.reset();
	aiPlayerSlot.reset(new AiPlayerSlot());
	
	for (s_p<Player>& player : kernel->players)
	{
		// Assigning Human's callback as this
		
		// @#~ don't uncomment till there will've been slot for all players, including AI
		if (player->playerType == HUMAN); // human
		else
			player->playerSlot = aiPlayerSlot.get();
	}
}

}
