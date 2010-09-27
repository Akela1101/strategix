/* 
 * File:   EntityManager.cpp
 * Author: Akela1101
 * 
 * Created on 22 Апрель 2010 г., 21:14
 */

#include "EntityManager.h"


namespace Sample1
{
	using namespace Ogre;

EntityManager::EntityManager(const String &name, SceneManager *sceneManager)
{
	this->name = name;
	this->sceneManager = sceneManager;

	Root::getSingletonPtr()->addFrameListener(this);
}

EntityManager::~EntityManager()
{
	// Bad ! 'Case it stays in Root on one frame !!!
	Root::getSingletonPtr()->removeFrameListener(this);

	// Using after this destructor
	// Root::getSingleton().renderOneFrame();
	// will prevent from "Segmentation fault"
}

}
