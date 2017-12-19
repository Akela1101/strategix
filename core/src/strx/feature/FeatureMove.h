#ifndef _FEATUREMOVE_H
#define    _FEATUREMOVE_H

#include "Feature.h"
#include "Interfaces.h"


namespace strx
{
class FeatureMove : public Feature
{
	const FeatureInfoMove* featureInfoMove; /// Link to tree
	MapCoord coord;       /// finish coordinate
	float radius;         /// finish point radius
	ICommand* iCommand;   /// feature started moving (can be null)
	
	float speed;
	float distance;
	float terrainQuality;
	RealCoord direction, next;
	u_p<MapPath> path;
	
public:
	FeatureMove(const FeatureInfo* featureInfo, Entity* entity);
	~FeatureMove();
	
	void Move(MapCoord coord, float radius, ICommand* iCommand);
	void Tick(float seconds) override;
	void Stop() override;

private:
	bool NextPoint();
	void RebuildPath();
};
}

#endif    /* _FEATUREMOVE_H */

