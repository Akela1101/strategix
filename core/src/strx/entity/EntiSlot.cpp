#include "Enti.h"
#include "EntiSlot.h"


namespace strx
{

EntiSlot::EntiSlot(Enti* enti) : enti(enti)
{
	enti->SetSlot(this);
}

EntiSlot::~EntiSlot() = default;

}
