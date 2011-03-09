/* 
 * File:   EntityManager.h
 * Author: Akela1101
 *
 * Created on 22 Апрель 2010 г., 21:14
 */

#ifndef _ENTITYMANAGER_H
#define	_ENTITYMANAGER_H

#include <Ogre.h>
#include "GameStructs.h"


namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;

	class ObjectTitle;

	class EntityManager
	{
	protected:
		String name;
		Strategix::MapCoord mapCoord; // Coordinates on Map
		SceneNode *node;
		Entity *entity;
		AnimationState *animationState;		

		ObjectTitle *objectTitle;

	public:
		EntityManager(const String &name, const Strategix::MapCoord &mapCoord);
		virtual ~EntityManager();
	};
}

#endif	/* _ENTITYMANAGER_H */

