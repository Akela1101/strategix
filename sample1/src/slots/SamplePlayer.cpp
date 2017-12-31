#include <strx/entity/Entity.h>
#include <strx/network/Message.h>
#include <graphics/SampleMapWidget.h>
#include <slots/SampleEntity.h>

#include "SamplePlayer.h"


namespace sample1
{
void SamplePlayer::EntityAdded(s_p<EntityMessage> entityMessage)
{
	auto entiSlot = new SampleEntity(move(entityMessage));
	entiSlots.emplace(entiSlot->GetId(), entiSlot);

//	QObject::connect(entiSlot, &SampleEntity::DoMoved, mapWidget, &SampleMapWidget::OnEntityMoved);
//	QObject::connect(entiSlot, &SampleEntity::DoMapMoved, mapWidget, &SampleMapWidget::OnEntityMapMoved);
}

void SamplePlayer::MineRemoved(IdType id)
{
	qInvoke(mapWidget, [=]() { mapWidget->OnMineRemoved(id); });
}
}
