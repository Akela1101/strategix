#pragma once

#include "Feature.h"


namespace strx
{
class FeatureAttack : public Feature
{
	const FeatureInfoAttack* featureInfoAttack; // link to tree
	s_p<Entity> target;
	HpType hitProgress;

public:
	FeatureAttack(const FeatureInfo* featureInfo, Entity* entity);

	bool Attack(s_p<Entity> target);
	void Tick(float seconds) override;
	void Stop() override;
	void Completed(bool done) override; // moving complete
};
}
