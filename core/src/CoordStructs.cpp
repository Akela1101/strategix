/*
 * File:   CoordStructs.h
 * Author: Akela1101
 *
 * Created on 20 Март 2011 г., 12:05
 */

#include "CoordStructs.h"


namespace Strategix
{
#ifndef MSCC // GCC

template<>
MapCoord::operator RealCoord() const
{
	return RealCoord(0.5 + x, 0.5 + y); // Center object in cell
}

#endif

}
