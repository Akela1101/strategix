#include <strx/entity/Entity.h>
#include <graphics/SampleMapWidget.h>
#include <slots/SampleEntity.h>

#include "SamplePlayer.h"


namespace sample1
{
void SamplePlayer::EntiAdded(Entity* entity)
{
	auto entiSlot = new SampleEntity(entity);
	entiSlots.emplace(entity->GetId(), entiSlot);
	
	QObject::connect(entiSlot, &SampleEntity::DoMoved, mapWidget, &SampleMapWidget::OnEntityMoved);
	QObject::connect(entiSlot, &SampleEntity::DoMapMoved, mapWidget, &SampleMapWidget::OnEntityMapMoved);
}

void SamplePlayer::MineRemoved(IdType id)
{
	QMetaObject::invokeMethod(mapWidget, [=]() { mapWidget->OnMineRemoved(id); });
}
}