/* 
 * File:   PlayerSlotFrameListener.h
 * Author: Akela1101
 *
 * Created on 13 Январь 2011 г., 21:23
 */

#ifndef _PLAYERSLOTFRAMELISTENER_H
#define	_PLAYERSLOTFRAMELISTENER_H

#include <PlayerSlot.h>

#include <Ogre.h>
#include <OgreFrameListener.h>
#include <MyGUI.h>
#include <list>

#include <Strategix_Forward.h>
#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

	class PlayerSlotFrameListener : public PlayerSlot, public FrameListener
	{
		sh_p<Kernel> kernel;
		sh_p<MyGUI::Gui> myGUI;
		MyGUI::StaticText *resourcesText;

	protected:
		std::list<sh_p<OObjectEntiSlot> > entiSlots; // Move to Interface Class
		std::list<sh_p<OObjectResource> > resources;

	public:
		PlayerSlotFrameListener(sh_p<Kernel> kernel, sh_p<MyGUI::Gui> myGUI);
		virtual ~PlayerSlotFrameListener() {}

		virtual bool frameRenderingQueued(const FrameEvent &event);

		virtual void OnAddEnti(Enti *enti);
		virtual void OnAddMapResource(sh_p<MapResource> mapResource);
		virtual void OnChangeResources(const Resources &newResources);
	};
}

#endif	/* _PLAYERSLOTFRAMELISTENER_H */

