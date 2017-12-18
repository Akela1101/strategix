#include <strx/entity/Entity.h>
#include <graphics/SampleMapWidget.h>
#include <slots/SampleEntiSlot.h>

#include "SamplePlayerSlot.h"


namespace sample1
{
void SamplePlayerSlot::EntiAdded(Entity* entity)
{
	auto entiSlot = new SampleEntiSlot(entity);
	entiSlots.emplace(entity->GetId(), entiSlot);
	
	QObject::connect(entiSlot, &SampleEntiSlot::DoMoved
			, mapWidget, &SampleMapWidget::OnEntityMoved, Qt::QueuedConnection);
	QObject::connect(entiSlot, &SampleEntiSlot::DoMapMoved
			, mapWidget, &SampleMapWidget::OnEntityMapMoved, Qt::QueuedConnection);
}
}