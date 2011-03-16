/* 
 * File:   EntityUnit.h
 * Author: Akela1101
 *
 * Created on 22 Апрель 2010 г., 21:14
 */

#ifndef _ENTITYUNIT_H
#define	_ENTITYUNIT_H

#include <Ogre.h>
#include "GameStructs.h"


namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;

	class ObjectTitle;

	class EntityUnit
	{
	protected:
		String name;
		Strategix::MapCoord mapCoord; // Coordinates on Map
		SceneNode *node;
		Entity *entity;
		AnimationState *animationState;		

		ObjectTitle *objectTitle;

	public:
		EntityUnit(const String &name, const Strategix::MapCoord &mapCoord);
		virtual ~EntityUnit();
	};
}

#endif	/* _ENTITYUNIT_H */

