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
	
	void OnMove(RealCoord coord) override;

signals:
	void DoEntityMoved(int entityId, RealCoord coord);
};
}

#endif //_SAMPLEENTISLOT_H
