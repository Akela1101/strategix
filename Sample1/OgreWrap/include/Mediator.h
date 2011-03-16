/* 
 * File:   Mediator.h
 * Author: Akela1101
 *
 * Created on 13 Январь 2011 г., 21:23
 */

#ifndef _MYUNIT_H
#define	_MYUNIT_H

#include "OgreFrameListener.h"

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

	class EntityUnit;

	class Mediator : public FrameListener
	{
		sh_p<Kernel> kernel;

	protected:
		std::list<sh_p<EntityUnit> > entityUnits;

	public:
		Mediator(sh_p<Kernel> kernel);
		virtual ~Mediator();
		virtual bool frameRenderingQueued(const FrameEvent &event);

		void AddEntityUnit(sh_p<EntityUnit> entityUnit);
	};
}

#endif	/* _MYUNIT_H */

