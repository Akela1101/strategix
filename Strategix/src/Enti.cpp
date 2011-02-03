/* 
 * File:   Enti.cpp
 * Author: Akela1101
 * 
 * Created on 4 Февраль 2011 г., 18:41
 */

#include "Enti.h"

Enti::Enti()
{
}

Enti::Enti(const Enti &_c)
{
	init(_c);
}

Enti &Enti::operator =(const Enti &_c)
{
	if( this != &_c )
	{
		init(_c);
	}
	return *this;
}

void Enti::init(const Enti &_c)
{
}

Enti::~Enti()
{
}

