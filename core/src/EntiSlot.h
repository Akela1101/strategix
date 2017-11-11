#ifndef _ENTISLOT_H
#define    _ENTISLOT_H

#include "Interfaces.h"

#include "Strategix_Forward.h"


namespace Strategix
{
class EntiSlot : public ITick, public IMove, public ICollect, public IHealth, public IAttack
{
public:
	s_p<Enti> enti;

public:
	EntiSlot(s_p<Enti> enti);
	virtual ~EntiSlot() = 0;

private:
	EntiSlot(const EntiSlot& _c);
	EntiSlot& operator=(const EntiSlot& _c);
};
}

#endif    /* _ENTISLOT_H */

