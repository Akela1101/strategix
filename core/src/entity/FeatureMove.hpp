#pragma once

#include "Feature.hpp"

namespace strx
{
class FeatureMove : public Feature
{
	const MoveFeatureInfo* const info;  ///< Link to tree
	s_p<Entity> target;                 ///< target entity (can be null)
	MapCoord coord;                     ///< finish coordinate
	float radius;                       ///< finish point radius
	Feature* mover;                     ///< feature started moving (can be null)

	float speed;
	float distance;
	float terrainQuality;
	RealCoord direction, next;
	u_p<MapPath> path;

public:
	FeatureMove(const FeatureInfo* featureInfo, Entity* entity);
	~FeatureMove();

	void Move(s_p<Entity> target, float radius, Feature* mover);
	void Move(MapCoord coord, float radius, Feature* mover);
	void Tick(float seconds) override;
	void Stop() override;

private:
	bool NextPoint();
	void RebuildPath();
};
}  // namespace strx
