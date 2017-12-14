#include <strx/feature/FeatureCollect.h>
#include <strx/feature/FeatureMove.h>
#include <strx/kernel/Kernel.h>

#include "Entity.h"
#include "EntitySlot.h"


namespace strx
{

EntitySlot::EntitySlot(Entity* entity) : entity(entity)
{
	entity->SetSlot(this);
	
	Kernel::Connect(DoMove, [entity] (MapCoord coord)
	{
		if (auto f = entity->Do<FeatureMove>()) f->Move(coord);
	});
	Kernel::Connect(DoCollect, [entity] (MapCoord coord, const string& resourceName)
	{
		if (auto f = entity->Do<FeatureCollect>()) f->Collect(coord, resourceName);
	});
}

EntitySlot::~EntitySlot() = default;

}
