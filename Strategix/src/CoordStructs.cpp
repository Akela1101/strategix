/*
 * File:   CoordStructs.h
 * Author: Akela1101
 *
 * Created on 20 Март 2011 г., 12:05
 */

#include "CoordStructs.h"

namespace Strategix
{
	extern const float tileSize; // Lenght of tile's side (KernelBase.cpp)

template<>
template<>
MapCoord::operator RealCoord() const
{
	return RealCoord((0.5 + x)*tileSize, (0.5 + y)*tileSize);
}

template<>
template<>
RealCoord::operator MapCoord() const
{
	return MapCoord(x/tileSize, y/tileSize);
}

}
