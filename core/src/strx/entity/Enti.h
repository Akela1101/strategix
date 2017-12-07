#ifndef _ENTI_H
#define _ENTI_H

#include <list>
#include <typeindex>

#include <Strategix_Forward.h>


namespace strx
{

class Enti
{
	EntiSlot* slot = nullptr; // Link to slot
	Player* const player;     // Link to owner
	const EntiInfo& entiInfo; // Link to tree
	const int id;             // unique id
	RealCoord coord;          // real coordinate
	
	using FeaturesType = umap<type_index, u_p<Feature>>;
	FeaturesType features;    // set of features
	
	Feature* tickFeature;     // current active feature getting Tick
	list<Feature*> passiveTickFeatures; // features not interfering with tickFeature
	/* ex.: regeneration, taking damage, etc. */
	
	bool isLastFeature;       // check if there is no new tickFeature before remove it

public:
	Enti(const EntiInfo& entiInfo, int id, const RealCoord& coord, Player* player);
	Enti(const Enti& _c) = delete;
	Enti& operator=(const Enti& _c) = delete;
	~Enti();
	
	EntiSlot& GetSlot() const { return *slot; }
	Player& GetPlayer() const { return *player; }
	const EntiInfo& GetInfo() const { return entiInfo; }
	int GetId() const { return id; }
	RealCoord GetCoord() const { return coord; }
	void SetSlot(EntiSlot* slot);
	
	void Tick(float seconds);
	void AssignTickFeature(Feature* feature, bool isPassive = false);
	
	template<typename F>
	F* Do() { return dynamic_cast<F*>(GetFeature(typeid(F))); }

private:
	Feature* GetFeature(type_index type) const;
	void AddFeature(const string& name, const FeatureInfo* featureInfo);
};
}
#endif    /* _ENTI_H */

