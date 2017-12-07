#include <strx/feature/FeatureMove.h>
#include <strx/kernel/Kernel.h>

#include "Enti.h"
#include "EntiSlot.h"


namespace strx
{

EntiSlot::EntiSlot(Enti* enti) : enti(enti)
{
	enti->SetSlot(this);
	
	Kernel::Connect(DoMove, [enti] (MapCoord coord) { if (auto f = enti->Do<FeatureMove>()) f->Move(coord); });
}

EntiSlot::~EntiSlot() = default;

}
