/* 
 * File:   Entity.cpp
 * Author: Akela1101
 * 
 * Created on 23 Июнь 2010 г., 16:05
 */

#include "Entity.h"

using namespace Strategix;

Entity::Entity()
{
}

Entity::Entity(const Entity &_c)
{
	init(_c);
}

Entity &Entity::operator =(const Entity &_c)
{
	if( this != &_c )
	{
		init(_c);
	}
	return *this;
}

void Entity::init(const Entity &_c)
{
}

Entity::~Entity()
{
}

