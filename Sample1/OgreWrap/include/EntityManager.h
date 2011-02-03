/* 
 * File:   EntityManager.h
 * Author: Akela1101
 *
 * Created on 22 Апрель 2010 г., 21:14
 */

#ifndef _ENTITYMANAGER_H
#define	_ENTITYMANAGER_H

#include <Ogre.h>
#include "OgreWrapCommon.h"
#include "ObjectTitle.h"
#include "GameStructs.h"
#include "MyManager.h"
#include "Player.h"


namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;

	//class MyManager;

	class EntityManager : public FrameListener
	{
	protected:
		Player *player; // Owner
		String name;
		SceneNode *node;
		Entity *entity;
		AnimationState *animationState;
		Strategix::MapCoord mapCoord; // Coordinates on Map

		ObjectTitle *objectTitle;

	public:
		EntityManager(Player *player, const String &name, const Strategix::MapCoord &mapCoord);
		void BeginDestruction(); // Don't redefine this! Must be called in place of destructor.
		virtual ~EntityManager();
	};
}

#endif	/* _ENTITYMANAGER_H */

