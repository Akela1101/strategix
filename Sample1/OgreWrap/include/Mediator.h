/* 
 * File:   Mediator.h
 * Author: Akela1101
 *
 * Created on 13 Январь 2011 г., 21:23
 */

#ifndef _MYMANAGER_H
#define	_MYMANAGER_H

#include "OgreFrameListener.h"

#include <list>

#include "Nya.hpp"


namespace Strategix
{
	class Game;
}

namespace Sample1
{
	using namespace std;

	class EntityManager;

	class Mediator : public FrameListener
	{
		Strategix::Game *game; // link to current game

	protected:
		std::list<sh_p<EntityManager> > entityManagers;

	public:
		Mediator();
		virtual ~Mediator();
		virtual bool frameRenderingQueued(const FrameEvent &event);

		void AddEntityManager(sh_p<EntityManager> entityManager);
	};
}

#endif	/* _MYMANAGER_H */

