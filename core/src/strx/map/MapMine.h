#ifndef _MapMine_H
#define _MapMine_H

#include <Strategix_Forward.h>
#include "MapObject.h"


namespace strx
{
struct MapMine : MapObject
{
	ResourceUnit amount;

public:
	MapMine(string name, RealCoord coord, ResourceUnit amount) : MapObject(move(name), coord), amount(amount) {}
	MapMine(const MapMine& other) : MapObject(other), amount(other.amount) {}
	MapMine* clone() override { return new MapMine(*this); }
	
	Resource GetResource() const { return Resource(name, amount); }
	ResourceUnit PickResource(ResourceUnit amountChange);
};
}

#endif //_MapMine_H

