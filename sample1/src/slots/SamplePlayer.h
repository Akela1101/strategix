#pragma once

#include <strx/player/PlayerSlot.h>
#include <Sample_fwd.h>
#include <QObject>

namespace sample1
{
class SampleEntity;

class SamplePlayer : public QObject, public PlayerSlot
{
Q_OBJECT
	using PlayerSlot::PlayerSlot;

	SampleMapWidget* mapWidget = nullptr;
	umap<IdType, u_p<SampleEntity>> entiSlots;

public:
	SampleEntity& GetEntitySlot(IdType id) { return *entiSlots[id]; }
	void SetMapWidget(SampleMapWidget* mapWidget) { this->mapWidget = mapWidget; }

// Callbacks:
	void EntityAdded(s_p<EntityMessage> entityMessage) override;
	void ResourcesChanged(const Resources& newResources) override { emit DoResourcesChanged(newResources); }
	void MineRemoved(IdType id) override;

signals:
	void DoResourcesChanged(Resources newResources);
};
}
