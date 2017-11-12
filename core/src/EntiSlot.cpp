#include "Enti.h"

#include "EntiSlot.h"


namespace Strategix
{

EntiSlot::EntiSlot(s_p<Enti>& enti) : enti(enti)
{
	enti->slot = this;
}

EntiSlot::~EntiSlot() {}

}
