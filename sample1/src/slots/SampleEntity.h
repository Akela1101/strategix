#pragma once

#include <Sample_fwd.h>
#include <strx/entity/EntitySlot.h>
#include <QObject>


namespace sample1
{
class SampleEntity : public QObject, public EntitySlot
{
Q_OBJECT
	using EntitySlot::EntitySlot;

private:
	void Moved(RealCoord coord) override { emit DoMoved(GetId(), coord); }
	void MapMoved(MapCoord from, MapCoord to) override { emit DoMapMoved(from, to); }

signals:
	void DoMoved(IdType id, RealCoord coord);
	void DoMapMoved(MapCoord from, MapCoord to);
};
}
