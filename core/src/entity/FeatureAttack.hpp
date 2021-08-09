#pragma once

#include "Feature.hpp"


namespace strx
{
class FeatureAttack : public Feature
{
	const AttackFeatureInfo* const info;  ///< link to tree
	s_p<EntityKernel> target;
	w_p<EntityKernel> movingTarget;
	float hitProgress;

public:
	FeatureAttack(const FeatureInfo* featureInfo, EntityKernel* entity);

	bool Attack(IdType targetId);
	void Tick(float seconds) override;
	void Stop() override;
	void Completed(bool done) override;  // moving complete
};
}  // namespace strx
