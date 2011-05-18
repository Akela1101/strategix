/* 
 * File:   OObjectResource.cpp
 * Author: Akela1101
 * 
 * Created on 13 Май 2011 г., 18:39
 */

#include "MapResource.h"

#include "MyAppCommon.h"

#include <Ogre.h>

#include "OObjectResource.h"


namespace Sample1
{

OObjectResource::OObjectResource(const std::string &meshName, sh_p<MapResource> mapResource)
	:
	OObject(meshName),
	mapResource(mapResource)
{
	entity->setUserAny(Any(this)); // Link from Entity
	entity->setQueryFlags(RES_MASK); // Mask for mouse selection

	RealCoord resourceCoord = mapResource->mapCoord; // convert to float
	node->setPosition(resourceCoord.x, 0, resourceCoord.y);
}

}
