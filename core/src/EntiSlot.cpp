#include "Enti.h"

#include "EntiSlot.h"


namespace Strategix
{

EntiSlot::EntiSlot(s_p<Enti> enti) : enti(enti)
{
	enti->entiSlot = this;
}

EntiSlot::~EntiSlot() {}

}
