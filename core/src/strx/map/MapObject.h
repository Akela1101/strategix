#pragma once

#include <Strategix_fwd.h>


namespace strx
{
struct MapObject
{
private:
	static IdType lastId;
	
public:
	IdType id;
	string name;
	RealCoord coord;
	
	MapObject(string name, RealCoord coord) : id(++lastId), name(move(name)), coord(coord) {}
	MapObject(const MapObject& other) : id(other.id), name(other.name), coord(other.coord) {}
	virtual ~MapObject() {}
	
	virtual MapObject* clone() = 0;
};

struct MapEntity : MapObject
{
	int owner;        // owner player id
	
	MapEntity(string name, RealCoord coord, int owner) : MapObject(move(name), coord), owner(owner) {}
	MapEntity(const MapEntity& other) : MapObject(other), owner(other.owner) {}
	MapObject* clone() override { return new MapEntity(*this); }
};

}
