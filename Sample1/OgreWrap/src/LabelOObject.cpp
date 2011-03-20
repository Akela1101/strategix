/* 
 * File:   LabelOObject.cpp
 * Author: Akela1101
 * 
 * Created on 23 Апрель 2010 г., 11:49
 */

#include "MyAppCommon.h"

#include <Ogre.h>

#include "LabelOObject.h"


namespace Sample1
{
	using namespace Ogre;

LabelOObject::LabelOObject(const std::string &meshName, const std::string &title, Strategix::MapCoord mapCoord)
	:
	TitledOObject(meshName, title),
	mapCoord(mapCoord)
{
	node->setPosition(Vector3((mapCoord.x + 0.5f) * tile_length, tile_length, (mapCoord.y + 0.5f) * tile_length));
	node->setVisible(false);
}

LabelOObject::~LabelOObject()
{
}

}