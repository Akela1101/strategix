#pragma once

#include "strx_fwd.hpp"


namespace strx
{
class Entity : boost::noncopyable
{
	s_p<EntityMessage> entityMessage;

public:
	Entity(s_p<EntityMessage> entityMessage);
	virtual ~Entity() = default;

	IdType GetId() const;
	HpType GetMaxHp() const;

	void Move(MapCoord coord);
	virtual void Collect(MapCoord coord, const string& resourceName);
	virtual void Attack(IdType targetId);

	virtual void Moved(RealCoord coord) = 0;
	virtual void MapMoved(MapCoord from, MapCoord to) {}
	virtual void HpChanged(HpType hp) {}
};
}  // namespace strx
