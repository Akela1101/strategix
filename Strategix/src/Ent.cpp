/* 
 * File:   Ent.cpp
 * Author: Akela1101
 * 
 * Created on 15 Январь 2011 г., 23:34
 */

#include "Ent.h"

Ent::Ent()
{
}

Ent::Ent(const Ent &_c)
{
	init(_c);
}

Ent &Ent::operator =(const Ent &_c)
{
	if( this != &_c )
	{
		init(_c);
	}
	return *this;
}

void Ent::init(const Ent &_c)
{
}

Ent::~Ent()
{
}

