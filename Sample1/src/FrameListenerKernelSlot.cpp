/* 
 * File:   FrameListenerKernelSlot.cpp
 * Author: Akela1101
 * 
 * Created on 4 Июнь 2011 г., 14:48
 */
#include "HumanPlayerSlot.h"

#include <Strategix.h>

#include "FrameListenerKernelSlot.h"


namespace Sample1
{
	using namespace Strategix;

FrameListenerKernelSlot::FrameListenerKernelSlot(sh_p<Kernel> kernel)
	:
	kernel(kernel)
{
	// PlayerSlot for HUMAN
	humanPlayerSlot.reset(new HumanPlayerSlot());

	foreach( sh_p<Player > &player, kernel->players )
	{
		// Assigning Human's callback as this
		if( player->playerType == HUMAN )
			player->playerSlot = humanPlayerSlot.get();		
	}
}

bool FrameListenerKernelSlot::frameRenderingQueued(const FrameEvent &event)
{
	kernel->Tick(event.timeSinceLastFrame); // Time transmitting to Strategix
	return true;
}

}
