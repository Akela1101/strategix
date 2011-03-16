/* 
 * File:   EntityUnit.cpp
 * Author: Akela1101
 * 
 * Created on 22 Апрель 2010 г., 21:14
 */

#include "EntityUnit.h"

namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;

EntityUnit::EntityUnit(const String &name, const Strategix::MapCoord &mapCoord)
	:
	name(name),
	mapCoord(mapCoord)
{
}

EntityUnit::~EntityUnit()
{
}

}
