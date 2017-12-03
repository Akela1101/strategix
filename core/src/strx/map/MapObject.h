#ifndef _MapObject_H
#define _MapObject_H

#include <Strategix_Forward.h>


namespace strx
{
struct MapObject
{
	string name;
	MapCoord coord;
	
	MapObject(string name, MapCoord coord) : name(move(name)), coord(coord) {}
	MapObject(const MapObject& other) : name(other.name), coord(other.coord) {}
	virtual ~MapObject() {}
	
	virtual MapObject* clone() = 0;
};

struct PlayerObject : MapObject
{
	int owner;        // owner player id
	
	PlayerObject(string name, MapCoord coord, int owner) : MapObject(move(name), coord), owner(owner) {}
	PlayerObject(const PlayerObject& other) : MapObject(other), owner(other.owner) {}
	MapObject* clone() override { return new PlayerObject(*this); }
};

struct MineObject : MapObject
{
	int amount;       // resource amount
	
	MineObject(string name, MapCoord coord, int amount) : MapObject(move(name), coord), amount(amount) {}
	MineObject(const MineObject& other) : MapObject(other), amount(other.amount) {}
	MapObject* clone() override { return new MineObject(*this); }
};

}
#endif //_MapObject_H
