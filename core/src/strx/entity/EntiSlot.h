#ifndef _ENTISLOT_H
#define    _ENTISLOT_H

#include <strx/feature/Interfaces.h>
#include <Strategix_Forward.h>


namespace strx
{
class EntiSlot : boost::noncopyable
		, public ITick, public IMove, public ICollect, public IHealth, public IAttack
{
protected:
	Enti* enti;
	
public:
	EntiSlot(Enti* enti);
	virtual ~EntiSlot() = 0;
};
}

#endif    /* _ENTISLOT_H */

