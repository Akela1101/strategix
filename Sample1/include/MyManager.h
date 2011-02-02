/* 
 * File:   MyManager.h
 * Author: Akela1101
 *
 * Created on 13 Январь 2011 г., 21:23
 */

#ifndef _MYMANAGER_H
#define	_MYMANAGER_H

#include "Nya.hpp"
#include "EntityManager.h"
#include <Ogre.h>
#include <list>

namespace Sample1
{
	using namespace std;

	class EntityManager;

	class MyManager
	{
	protected:
		std::list<sh_p<EntityManager> > entityManagers;

	public:
		SceneManager *sceneManager;

	public:
		MyManager();
		virtual ~MyManager();
		void AddEntityManager(sh_p<EntityManager> entityManager);
	};
}

#endif	/* _MYMANAGER_H */

