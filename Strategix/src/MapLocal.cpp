/* 
 * File:   MapLocal.cpp
 * Author: Akela1101
 * 
 * Created on 24 Март 2011 г., 14:02
 */

#include "MapLocal.h"
#include "MapsPathsFinder.h"


namespace Strategix
{

MapLocal::MapLocal()
	:
	pathsFinder(new MapsPathsFinder())
{
}

MapLocal::~MapLocal()
{
}

sh_p<MapsPath> MapLocal::FindPath(const MapCoord from, const MapCoord till)
{
	return pathsFinder->FindPath(from, till);
}

}
