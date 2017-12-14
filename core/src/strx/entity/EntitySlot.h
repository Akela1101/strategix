#ifndef _ENTISLOT_H
#define    _ENTISLOT_H

#include <strx/feature/Interfaces.h>
#include <Strategix_Forward.h>


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

#endif    /* _ENTISLOT_H */

