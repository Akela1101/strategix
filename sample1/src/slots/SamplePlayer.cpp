#include <strx/entity/Entity.h>
#include <strx/kernel/Message.h>
#include <graphics/SampleMapWidget.h>
#include <slots/SampleEntity.h>

#include "SamplePlayer.h"


namespace sample1
{
void SamplePlayer::EntityAdded(s_p<EntityMessage> entityMessage)
{
	auto entiSlot = make_u<SampleEntity>(move(entityMessage));
	connect(entiSlot.get(), &SampleEntity::DoMoved, mapWidget, &SampleMapWidget::OnEntityMoved);
	connect(entiSlot.get(), &SampleEntity::DoMapMoved, mapWidget, &SampleMapWidget::OnEntityMapMoved);

	entiSlots.emplace(entiSlot->GetId(), move(entiSlot));
}

void SamplePlayer::MineRemoved(IdType id)
{
	qInvoke(mapWidget, [=]() { mapWidget->OnMineRemoved(id); });
}
}
