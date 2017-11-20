#ifndef _FEATUREMOVE_H
#define    _FEATUREMOVE_H

#include "Feature.h"
#include "Interfaces.h"

#include "strx/common/Strategix_Forward.h"


namespace strx
{
class FeatureMove : public Feature
{
protected:
	const FeatureInfoMove* featureInfoMove; // Link to tree
	float speed;
	
	bool isMoving;

private:
	float distance;
	RealCoord direction, finish;
	s_p<MapsPath> mapsPath;
	
	ICommand* iCommand; // someone who started moving

public:
	FeatureMove(const FeatureInfo* featureInfo, Enti* enti);
	
	bool Move(RealCoord newCoord, ICommand* iCommand = 0);
	virtual bool Tick(float seconds);
	virtual void Stop();

private:
	FeatureMove(const FeatureMove& _c);
	FeatureMove& operator=(const FeatureMove& _c);
};
}

#endif    /* _FEATUREMOVE_H */

