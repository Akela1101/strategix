#pragma once

#include "Feature.h"


namespace strx
{
class FeatureHealth : public Feature
{
protected:
	const FeatureInfoHealth* featureInfoHealth; // Link to tree

private:
	HpType hp;

public:
	FeatureHealth(const FeatureInfo* featureInfo, Entity* entity);
	
	void Tick(float seconds) override;
	void Stop() override;
	
	const HpType GetHp() const { return hp; }
	
	const HpType GetMaxHp() const;
	bool HpChange(HpType deltaHp); // false if become dead
};
}
