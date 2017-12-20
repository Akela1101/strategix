#pragma once

#include <Strategix_fwd.h>
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
	
	ResourceUnit PickResource(ResourceUnit amountChange);
};
}
