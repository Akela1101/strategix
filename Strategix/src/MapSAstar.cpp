/* 
 * File:   MapSAstar.cpp
 * Author: Akela1101
 * 
 * Created on 20 Апрель 2010 г., 9:14
 */

#include "MapSAstar.h"

MapSAstar::MapSAstar()
{
}

MapSAstar::MapSAstar(const MapSAstar &_c)
{
	init(_c);
}

MapSAstar &MapSAstar::operator =(const MapSAstar &_c)
{
	if( this != &_c )
	{
		init(_c);
	}
	return *this;
}

void MapSAstar::init(const MapSAstar &_c)
{
}

MapSAstar::~MapSAstar()
{
}

