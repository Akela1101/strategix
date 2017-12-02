#ifndef _FEATURECOLLECT_H
#define    _FEATURECOLLECT_H

#include "Feature.h"
#include "Interfaces.h"



namespace strx
{
class FeatureCollect : public Feature, public ICommand
{
protected:
	const FeatureInfoCollect* featureInfoCollect; // Link to tree
	float capacity; // amount of resource Enti can hold
	string resourceName;

private:
	float load; // amount of resource Enti is holding
	Mine* mine; // target
	bool isMovingToCollector;

public:
	FeatureCollect(const FeatureInfo* featureInfo, Enti* enti);
	
	bool Collect(Mine* mine);
	virtual bool Tick(float seconds);
	virtual void Stop();
	
	virtual void OnComplete(bool isComplete); // Moving Complete

protected:
	const Enti* FindCollector(); // resource collector
	void MoveToCollector(); // going back to base(or other collector)

private:
	FeatureCollect(const FeatureCollect& _c);
	FeatureCollect& operator=(const FeatureCollect& _c);
};
}

#endif    /* _FEATURECOLLECT_H */

