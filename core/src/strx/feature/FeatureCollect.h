#ifndef _FEATURECOLLECT_H
#define    _FEATURECOLLECT_H

#include "Feature.h"
#include "Interfaces.h"



namespace strx
{
class FeatureCollect : public Feature, public ICommand
{
	const FeatureInfoCollect* featureInfoCollect; /// Link to tree
	MapCoord coord;             /// coordinate to search for resources
	string resourceName;        /// resource name
	float capacity;             /// amount of resource Enti can hold
	float load;                 /// amount of resource Enti is holding
	bool isMovingToCollector;   /// to collector | from collector

public:
	FeatureCollect(const FeatureInfo* featureInfo, Entity* entity);
	
	bool Collect(MapCoord coord, const string& resourceName);
	
	virtual void Tick(float seconds);
	virtual void Stop();
	virtual void OnComplete(bool isComplete); // moving complete

private:
	const Entity* FindCollector(); // resource collector
	void MoveToCollector(); // going back to base(or other collector)
};
}

#endif    /* _FEATURECOLLECT_H */

