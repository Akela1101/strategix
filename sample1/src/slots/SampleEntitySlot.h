#pragma once

#include <Sample_Forward.h>
#include <strx/entity/EntitySlot.h>
#include <QObject>


namespace sample1
{
class SampleEntitySlot : public QObject, public EntitySlot
{
Q_OBJECT
public:
	SampleEntitySlot(Entity* entity);

protected:
	void OnMove(RealCoord coord) override;
	void OnMapMove(MapCoord from, MapCoord to) override { emit DoMapMoved(from, to); }

signals:
	void DoMoved(IdType id, RealCoord coord);
	void DoMapMoved(MapCoord from, MapCoord to);
};
}
