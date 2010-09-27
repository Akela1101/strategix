/* 
 * File:   EntityInfo.cpp
 * Author: Akela1101
 * 
 * Created on 12 Март 2010 г., 18:34
 */

#include "EntityInfo.h"

using namespace Strategix;


EntityInfo::EntityInfo()
{
}

EntityInfo::EntityInfo(const EntityInfo &_c)
{
	init(_c);
}

EntityInfo &EntityInfo::operator =(const EntityInfo &_c)
{
	if( this != &_c )
	{
		init(_c);
	}
	return *this;
}

void EntityInfo::init(const EntityInfo &_c)
{
}

EntityInfo::~EntityInfo()
{
}

