#ifndef _ENTISLOT_H
#define    _ENTISLOT_H

#include <strx/feature/Interfaces.h>
#include <Strategix_Forward.h>


namespace strx
{
class EntiSlot : public ITick, public IMove, public ICollect, public IHealth, public IAttack
{
	Enti* enti;
	
public:
	EntiSlot(Enti* enti) : enti(enti) {}
	virtual ~EntiSlot() = 0;
	EntiSlot(const EntiSlot& _c) = delete;
	EntiSlot& operator=(const EntiSlot& _c) = delete;
	
	//const string& GetName() const { return name; }
};
}

#endif    /* _ENTISLOT_H */

