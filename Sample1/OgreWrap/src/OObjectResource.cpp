/* 
 * File:   OObjectResource.cpp
 * Author: Akela1101
 * 
 * Created on 13 Май 2011 г., 18:39
 */

#include <Ogre.h>

#include "OObjectResource.h"
#include "MyAppCommon.h"


namespace Sample1
{

OObjectResource::OObjectResource(const std::string &meshName, const RealCoord &coord)
	:
	OObject(meshName)
{
	entity->setQueryFlags(RES_MASK); // Mask for mouse selection

	node->setPosition(coord.x, 0, coord.y);
}

}
