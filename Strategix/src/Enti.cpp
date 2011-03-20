/* 
 * File:   Enti.cpp
 * Author: Akela1101
 * 
 * Created on 4 Февраль 2011 г., 18:41
 */

#include "Player.h"
#include "EntiInfo.h"

#include "Enti.h"


namespace Strategix
{

Enti::Enti(const EntiInfo *ei, const MapCoord &mapCoord)
	:
	ei(ei),
	mapCoord(mapCoord)
{
}

Enti::~Enti()
{
}

}