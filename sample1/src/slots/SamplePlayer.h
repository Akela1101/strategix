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

public:
	void ResourcesChanged(const Resources& newResources) override { emit DoResourcesChanged(newResources); }

signals:
	void DoResourcesChanged(Resources newResources);
};
}
