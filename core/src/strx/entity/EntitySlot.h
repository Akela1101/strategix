#pragma once

#include <strx/feature/Interfaces.h>
#include <Strategix_fwd.h>


namespace strx
{
class EntitySlot : boost::noncopyable
        , public IMove, public ICollect, public IHealth, public IAttack
{
	s_p<EntityMessage> entityMessage;

public:
	EntitySlot(s_p<EntityMessage> entityMessage);
	virtual ~EntitySlot() {}

	IdType GetId() const;
};
}
