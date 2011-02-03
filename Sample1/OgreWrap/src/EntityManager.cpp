/* 
 * File:   EntityManager.cpp
 * Author: Akela1101
 * 
 * Created on 22 Апрель 2010 г., 21:14
 */

#include "EntityManager.h"

namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;

EntityManager::EntityManager(Player *player, const String &name, const Strategix::MapCoord &mapCoord)
	:
	player(player),
	name(name),
	mapCoord(mapCoord)
{
	Root::getSingleton().addFrameListener(this);
}

void EntityManager::BeginDestruction()
{
	Root::getSingleton().removeFrameListener(this);

	// Add to deletion list
	//
}

EntityManager::~EntityManager()
{	
	// removeFrameListener must be earier than this destructor on one frame
	// elsewise there will be try to render deleted object!!!
	// Solution is to add this object to deletion list, called after one frame.
	// Or to hit on the head someone from OGRE developers :)
}

}
