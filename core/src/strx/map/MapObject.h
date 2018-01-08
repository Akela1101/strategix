#pragma once

#include <Strategix_fwd.h>


namespace strx
{
struct MapObject
{
	IdType id;            /// globally unique id
	string name;          /// object type name, like "worker" or "barracks"
	RealCoord coord;      /// precise coord

	MapObject(IdType id, string name, RealCoord coord) : id(id), name(move(name)), coord(coord) {}
	MapObject(const MapObject& other) : id(other.id), name(other.name), coord(other.coord) {}
	virtual ~MapObject() {}
	virtual MapObject* clone() = 0;
};

struct MapEntity : MapObject
{
	int ownerSpot;        /// owner player spot
	HpType hp;            /// HP
	HpType maxHp;         /// max HP

	MapEntity(IdType id, string name, RealCoord coord, int ownerSpot)
	    : MapObject(id, move(name), coord), ownerSpot(ownerSpot), hp(0), maxHp(1) {}
	MapEntity(const MapEntity& other) : MapObject(other), ownerSpot(other.ownerSpot) {}
	MapObject* clone() override { return new MapEntity(*this); }

	void SetMaxHp(HpType initHp) { hp = maxHp = initHp; }
};

}
