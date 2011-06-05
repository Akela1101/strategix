/* 
 * File:   FrameListenerKernelSlot.h
 * Author: Akela1101
 *
 * Created on 4 Июнь 2011 г., 14:48
 */

#ifndef _FRAMELISTENERKERNELSLOT_H
#define	_FRAMELISTENERKERNELSLOT_H

#include <OgreFrameListener.h>

#include <Strategix_Forward.h>
#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace Ogre;
	using namespace Strategix;

	class FrameListenerKernelSlot : public FrameListener
	{
		sh_p<Kernel> kernel;
		sh_p<HumanPlayerSlot> humanPlayerSlot;

	public:
		FrameListenerKernelSlot(sh_p<Kernel> kernel);
		virtual ~FrameListenerKernelSlot() {}

		virtual bool frameRenderingQueued(const FrameEvent &event);
	};

}

#endif	/* _FRAMELISTENERKERNELSLOT_H */

