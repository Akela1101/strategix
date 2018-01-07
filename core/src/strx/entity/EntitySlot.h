#pragma once

#include <Strategix_fwd.h>


namespace strx
{
class EntitySlot : boost::noncopyable
{
	s_p<EntityMessage> entityMessage;

public:
	EntitySlot(s_p<EntityMessage> entityMessage);
	virtual ~EntitySlot() {}

	IdType GetId() const;

	void Move(MapCoord coord);
	void Collect(MapCoord coord, const string& resourceName);
	void Attack(IdType targetId);

	virtual void Moved(RealCoord coord) = 0;
	virtual void MapMoved(MapCoord from, MapCoord to) {}
	virtual void HpChanged() {}
	virtual void Attacked() {}
};
}
