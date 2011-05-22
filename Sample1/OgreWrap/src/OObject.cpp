/* 
 * File:   OObject.cpp
 * Author: Akela1101
 * 
 * Created on 18 Март 2011 г., 15:44
 */

#include "MyAppCommon.h"

#include <Ogre.h>

#include "OObject.h"


namespace Sample1
{

OObject::OObject(const std::string meshName)
{	
	entity = sceneManager->createEntity(meshName);	
	node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(entity);
}

OObject::~OObject()
{
	node->detachObject(entity);
	sceneManager->destroyEntity(entity);
	sceneManager->destroySceneNode(node);
}

}

