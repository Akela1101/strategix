#pragma once

#include "Feature.h"
#include "Interfaces.h"


namespace strx
{
class FeatureAttack : public Feature, public ICommand
{
protected:
	const FeatureInfoAttack* featureInfoAttack; // Link to tree

private:
	s_p<Entity> target;
	HpType hitProgress;

public:
	FeatureAttack(const FeatureInfo* featureInfo, Entity* entity);
	
	bool Attack(s_p<Entity> target);
	virtual void Tick(float seconds);
	virtual void Stop();
	virtual void OnComplete(bool isComplete); // Moving Complete
};
}
