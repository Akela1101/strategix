#ifndef _SAMPLEENTISLOT_H
#define _SAMPLEENTISLOT_H

#include <Sample_Forward.h>
#include <strx/entity/EntitySlot.h>
#include <QObject>


namespace sample1
{
class SampleEntiSlot : public QObject, public EntitySlot
{
Q_OBJECT
public:
	SampleEntiSlot(Entity* entity);

protected:
	void OnMove(RealCoord coord) override;
	void OnMapMove(MapCoord from, MapCoord to) override;

signals:
	void DoMoved(int entityId, RealCoord coord);
	void DoMapMoved(MapCoord from, MapCoord to);
};
}

#endif //_SAMPLEENTISLOT_H
