#pragma once

#include "Feature.h"


namespace strx
{
class FeatureCollect : public Feature
{
	const FeatureInfoCollect* const info; /// Link to tree
	MapCoord coord;             /// coordinate to search for resources
	string resourceName;        /// resource name
	ResourceUnit capacity;      /// amount of resource Entity can hold
	ResourceUnit load;          /// amount of resource Entity is holding
	bool isMovingToCollector;   /// to collector | from collector

public:
	FeatureCollect(const FeatureInfo* featureInfo, Entity* entity);

	bool Collect(MapCoord coord, const string& resourceName);

	void Tick(float seconds) override;
	void Stop() override;
	void Completed(bool done) override; // moving complete

private:
	void Collect(MapCoord coord);
	void MoveToCollector(); // going back to base(or other collector)
	MapMine* SelectMine();
};
}
