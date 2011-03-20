/* 
 * File:   TitledOObject.cpp
 * Author: Akela1101
 * 
 * Created on 18 Март 2011 г., 19:03
 */

#include <Ogre.h>

#include "TitledOObject.h"


namespace Sample1
{

TitledOObject::TitledOObject(const std::string &meshName, const std::string &title)
	:
	OObject(meshName),
	objectTitle(new ObjectTitle(entity, title, "Calibri"))
{	
}

TitledOObject::~TitledOObject()
{
}

}
