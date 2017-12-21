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
	umap<int, u_p<SampleEntity>> entiSlots;
	
public:
	SampleEntity& GetEntitySlot(int id) { return *entiSlots[id].get(); }
	void SetMapWidget(SampleMapWidget* mapWidget) { this->mapWidget = mapWidget; }

protected:
	void EntiAdded(Entity* entity) override;
	void EntiRemoved(Entity* entity) override {}
	void ResourcesChanged(const Resources& newResources) override { emit DoResourcesChanged(newResources); }
	void MineRemoved(IdType id) override;
	
signals:
	void DoResourcesChanged(Resources newResources);
};
}
