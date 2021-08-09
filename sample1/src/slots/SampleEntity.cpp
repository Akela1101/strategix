#include <graphics/SampleMapWidget.hpp>

#include "SampleEntity.hpp"


namespace sample1
{

SampleEntity::SampleEntity(s_p<EntityMessage> entityMessage, SampleMapWidget* mapWidget)
        : EntitySlot(move(entityMessage)), mapWidget(mapWidget)
{}

void SampleEntity::Moved(RealCoord coord)
{
	mapWidget->OnEntityMoved(GetId(), coord);
}

void SampleEntity::MapMoved(MapCoord from, MapCoord to)
{
	mapWidget->OnEntityMapMoved(from, to);
}

void SampleEntity::HpChanged(HpType hp)
{
	mapWidget->OnEntityHpChanged(GetId(), hp);
}

}  // namespace sample1
