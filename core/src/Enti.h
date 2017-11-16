#ifndef _ENTI_H
#define _ENTI_H

#ifdef MSCC
#include "EntiInfo.h"
#endif

#include "FeatureMove.h"
#include "FeatureCollect.h"
#include "FeatureHealth.h"
#include "FeatureAttack.h"

#include <map>
#include <list>
#include <string>
#include <typeinfo>

#include "Strategix_Forward.h"


namespace strategix
{
using namespace std;

class Enti
{
	friend class EntiSlot;
	friend class Player;
	
	EntiSlot* slot;           // Link to slot
	Player* player;           // Link to owner
	const EntiInfo& entiInfo; // Link to tree
	RealCoord coord;          // real coordinate
	
	using FeaturesType = map<string, s_p<Feature>>;
	FeaturesType features;    // map[typeid.name]
	
	Feature* tickFeature;     // current active feature getting Tick
	list<Feature*> passiveTickFeatures; // features not interfering with tickFeature
	/* ex.: regeneration, taking damage, etc. */
	
	bool isLastFeature;       // check if there is no new tickFeature before remove it

public:
	Enti(const EntiInfo& entiInfo, const RealCoord& coord);
	Enti(const Enti& _c) = delete;
	Enti& operator=(const Enti& _c) = delete;
	
	EntiSlot& GetSlot() const { return *slot; }
	Player& GetPlayer() const { return *player; }
	const EntiInfo& GetInfo() const { return entiInfo; }
	RealCoord GetCoord() const { return coord; }
	
	void Tick(float seconds);
	void AssignTickFeature(Feature* feature, bool isPassive = false);
	
	template<typename F>
	F* Do() // get feature with type F
	{
		const string featureName = typeid(F).name();
		FeaturesType::iterator iFeature = features.find(featureName);
		if (iFeature != features.end())
		{
			return dynamic_cast<F*>(iFeature->second.get());
		}
		throw_nya("There is no feature named: " + featureName);
	}

private:
	void AddFeature(const string& name, const FeatureInfo* featureInfo);
};
}
#endif    /* _ENTI_H */

