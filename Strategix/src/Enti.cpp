/* 
 * File:   Enti.cpp
 * Author: Akela1101
 * 
 * Created on 4 Февраль 2011 г., 18:41
 */

#include "Player.h"
#include "EntiInfo.h"

#include "Enti.h"


using namespace Strategix;


template<class Unit>
Enti<Unit>::Enti(Player *player, const EntiInfo *ei, const MapCoord &mapCoord)
	:
	player(player),
	ei(ei),
	mapCoord(mapCoord)
{
}

/*
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
*/

template<class Unit>
Enti<Unit>::~Enti()
{
}

