#pragma once

#include "Feature.hpp"


namespace strx
{
class FeatureAttack : public Feature
{
	const AttackFeatureInfo* const info;  ///< link to tree
	s_p<Entity> target;
	w_p<Entity> movingTarget;
	float hitProgress;

public:
	FeatureAttack(const FeatureInfo* featureInfo, Entity* entity);

	bool Attack(IdType targetId);
	void Tick(float seconds) override;
	void Stop() override;
	void Completed(bool done) override;  // moving complete
};
}  // namespace strx
