/* 
 * File:   EntityManager.h
 * Author: Akela1101
 *
 * Created on 22 Апрель 2010 г., 21:14
 */

#ifndef _ENTITYMANAGER_H
#define	_ENTITYMANAGER_H

#include <Ogre.h>

namespace Sample1
{
	using namespace Ogre;

	class EntityManager : public FrameListener
	{
	protected:
		String name;
		SceneManager *sceneManager;
		SceneNode *node;
		Entity *entity;

	public:
		EntityManager(const String &name, SceneManager *sceneManager);
		virtual ~EntityManager();
	};
}

#endif	/* _ENTITYMANAGER_H */

