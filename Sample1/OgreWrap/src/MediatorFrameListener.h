/* 
 * File:   MediatorFrameListener.h
 * Author: Akela1101
 *
 * Created on 13 Январь 2011 г., 21:23
 */

#ifndef _MEDIATORFRAMELISTENER_H
#define	_MEDIATORFRAMELISTENER_H

#include "Mediator.h"
#include "StrategixCommon.h"

#include <OgreFrameListener.h>

#include <list>

#include "Nya.hpp"


namespace Strategix
{
	class Kernel;
}

namespace MyGUI
{
	class Gui;
	class StaticText;
}

namespace Sample1
{
	using namespace std;
	using namespace Strategix;

	class OObjectUnit;
	class OObjectResource;

	class MediatorFrameListener : public Mediator, public FrameListener
	{
		sh_p<Kernel> kernel;
		sh_p<MyGUI::Gui> myGUI;
		MyGUI::StaticText *resourcesText;

	protected:
		std::list<sh_p<OObjectUnit> > units; // Move to Interface Class
		std::list<sh_p<OObjectResource> > resources;

	public:
		MediatorFrameListener(sh_p<Kernel> kernel, sh_p<MyGUI::Gui> myGUI);
		virtual ~MediatorFrameListener() {}

		virtual bool frameRenderingQueued(const FrameEvent &event);

		virtual void OnAddEnti(Enti *enti);
		virtual void OnChangeResources(const Resources &newResources);
	};
}

#endif	/* _MEDIATORFRAMELISTENER_H */

