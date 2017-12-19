#include <strx/entity/Entity.h>
#include <graphics/SampleMapWidget.h>
#include <slots/SampleEntitySlot.h>

#include "SamplePlayerSlot.h"


namespace sample1
{
void SamplePlayerSlot::EntiAdded(Entity* entity)
{
	auto entiSlot = new SampleEntitySlot(entity);
	entiSlots.emplace(entity->GetId(), entiSlot);
	
	QObject::connect(entiSlot, &SampleEntitySlot::DoMoved, mapWidget, &SampleMapWidget::OnEntityMoved);
	QObject::connect(entiSlot, &SampleEntitySlot::DoMapMoved, mapWidget, &SampleMapWidget::OnEntityMapMoved);
}

void SamplePlayerSlot::MineRemoved(IdType id)
{
	QMetaObject::invokeMethod(mapWidget, [=]() { mapWidget->OnMineRemoved(id); });
}
}