#ifndef _FEATUREMOVE_H
#define    _FEATUREMOVE_H

#include "Feature.h"
#include "Interfaces.h"


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
	u_p<MapPath> mapsPath;
	
	ICommand* iCommand; // someone who started moving

public:
	FeatureMove(const FeatureInfo* featureInfo, Enti* enti);
	~FeatureMove();
	
	bool Move(MapCoord coord, ICommand* iCommand = nullptr);
	bool Tick(float seconds) override;
	void Stop() override;
};
}

#endif    /* _FEATUREMOVE_H */

