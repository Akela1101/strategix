#ifndef _MapObject_H
#define _MapObject_H

#include <Strategix_Forward.h>


namespace strx
{
struct MapObject
{
	string name;
	RealCoord coord;
	
	MapObject(string name, RealCoord coord) : name(move(name)), coord(coord) {}
	MapObject(const MapObject& other) : name(other.name), coord(other.coord) {}
	virtual ~MapObject() {}
	
	virtual MapObject* clone() = 0;
};

struct EntityObject : MapObject
{
	int owner;        // owner player id
	
	EntityObject(string name, RealCoord coord, int owner) : MapObject(move(name), coord), owner(owner) {}
	EntityObject(const EntityObject& other) : MapObject(other), owner(other.owner) {}
	MapObject* clone() override { return new EntityObject(*this); }
};

struct MineObject : MapObject
{
	int amount;       // resource amount
	
	MineObject(string name, RealCoord coord, int amount) : MapObject(move(name), coord), amount(amount) {}
	MineObject(const MineObject& other) : MapObject(other), amount(other.amount) {}
	MapObject* clone() override { return new MineObject(*this); }
};

}
#endif //_MapObject_H
