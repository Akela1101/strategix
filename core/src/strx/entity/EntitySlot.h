#pragma once

#include <strx/feature/Interfaces.h>
#include <Strategix_fwd.h>


namespace strx
{
class EntitySlot : boost::noncopyable
		, public ITick, public IMove, public ICollect, public IHealth, public IAttack
{
protected:
	Entity* entity;
	
public:
	EntitySlot(Entity* entity);
	virtual ~EntitySlot() = 0;
};
}
