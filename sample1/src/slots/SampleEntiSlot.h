#ifndef _SAMPLEENTISLOT_H
#define _SAMPLEENTISLOT_H

#include <strx/entity/EntiSlot.h>
#include <QObject>


namespace sample1
{
using namespace strx;

class SampleEntiSlot : public QObject, public EntiSlot
{
Q_OBJECT
public:
	SampleEntiSlot(Enti* enti);
	
	void OnMove(RealCoord coord) override;

signals:
	void DoEntityMoved(int entityId, RealCoord coord);
};
}

#endif //_SAMPLEENTISLOT_H
