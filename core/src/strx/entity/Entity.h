#ifndef _ENTI_H
#define _ENTI_H

#include <typeindex>
#include <Strategix_Forward.h>


namespace strx
{

class Entity : boost::noncopyable
{
	EntitySlot* slot = nullptr; /// link to slot
	Player* const player;     /// link to owner
	const EntityInfo& entiInfo; /// link to tree
	const int id;             /// unique id
	RealCoord coord;          /// real coordinate
	
	using FeaturesType = umap<type_index, u_p<Feature>>;
	FeaturesType features;    /// set of features
	
	Feature* task;            /// current active feature
	vector<Feature*> passiveTasks; /// entity routines
	/* ex.: regeneration, taking damage, etc. */
	
public:
	Entity(const EntityInfo& entiInfo, int id, const RealCoord& coord, Player* player);
	~Entity();
	
	EntitySlot& GetSlot() const { return *slot; }
	Player& GetPlayer() const { return *player; }
	const EntityInfo& GetInfo() const { return entiInfo; }
	int GetId() const { return id; }
	const RealCoord GetCoord() const { return coord; }
	RealCoord& GetCoord() { return coord; }
	void SetSlot(EntitySlot* slot);
	
	void Tick(float seconds);
	void AssignTask(Feature* feature);
	void AssignPassiveTask(Feature* feature);
	
	template<typename F>
	F* Do() { return dynamic_cast<F*>(GetFeature(typeid(F))); }

private:
	Feature* GetFeature(type_index type) const;
	void AddFeature(const string& name, const FeatureInfo* featureInfo);
};
}
#endif    /* _ENTI_H */

