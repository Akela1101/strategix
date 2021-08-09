#pragma once

#include "Feature.hpp"


namespace strx
{
class FeatureHealth : public Feature
{
	const HealthFeatureInfo* const info;  ///< Link to tree
	HpType hp;

public:
	FeatureHealth(const FeatureInfo* featureInfo, EntityKernel* entity);

	HpType GetHp() const { return hp; }
	const HpType GetMaxHp() const;

	void Tick(float seconds) override;

	/**
	 * Change HP.
	 * @param deltaHp hp difference (should be less than zero to reduce hp)
	 * @return false if destroied
	 */
	bool ChangeHp(HpType deltaHp);
};
}  // namespace strx
