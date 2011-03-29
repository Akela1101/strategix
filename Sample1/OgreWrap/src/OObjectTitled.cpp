/* 
 * File:   OObjectTitled.cpp
 * Author: Akela1101
 * 
 * Created on 18 Март 2011 г., 19:03
 */

#include <Ogre.h>

#include "OObjectTitled.h"


namespace Sample1
{

OObjectTitled::OObjectTitled(const std::string &meshName, const std::string &title)
	:
	OObject(meshName),
	objectTitle(new ObjectTitle(entity, title, "Calibri"))
{	
}

OObjectTitled::~OObjectTitled()
{
}

}
