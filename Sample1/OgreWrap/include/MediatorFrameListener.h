/* 
 * File:   MediatorFrameListener.h
 * Author: Akela1101
 *
 * Created on 13 Январь 2011 г., 21:23
 */

#ifndef _MEDIATORFRAMELISTENER_H
#define	_MEDIATORFRAMELISTENER_H

#include "Mediator.h"

#include <OgreFrameListener.h>

#include <list>

#include "Nya.hpp"


namespace Strategix
{
	class Kernel;
}

namespace Sample1
{
	using namespace std;
	using namespace Strategix;

	class OObjectUnit;
	class OObjectResource;

	class MediatorFrameListener : public Strategix::Mediator, public FrameListener
	{
		sh_p<Kernel> kernel;

	protected:
		std::list<sh_p<OObjectUnit> > units; // Move to Interface Class
		std::list<sh_p<OObjectResource> > resources;

	public:
		MediatorFrameListener(sh_p<Kernel> kernel);
		virtual ~MediatorFrameListener() {}
		
		virtual void OnAddEnti(Enti *enti);

		virtual bool frameRenderingQueued(const FrameEvent &event);
	};
}

#endif	/* _MEDIATORFRAMELISTENER_H */

