#pragma once

#include <typeindex>
#include <Strategix_fwd.h>


namespace strx
{

class Entity : boost::noncopyable
{
	Player* const player;        /// link to owner
	const EntityInfo& entiInfo;  /// link to tree
	const IdType id;             /// unique id
	RealCoord coord;             /// real coordinate
	MapCoord mapCoord;           /// discreet coordinate of object

	using FeaturesType = umap<type_index, u_p<Feature>>;
	FeaturesType features;       /// set of features

	Feature* task;               /// current active feature
	vector<Feature*> passiveTasks; /// entity routines
	/* ex.: regeneration, taking damage, etc. */

public:
	Entity(const EntityInfo& entiInfo, IdType id, RealCoord coord, Player* player);
	~Entity();

	Player& GetPlayer() const { return *player; }
	const EntityInfo& GetInfo() const { return entiInfo; }
	int GetId() const { return id; }
	RealCoord GetCoord() const { return coord; }
	MapCoord GetMapCoord() const { return mapCoord; }

	/// receive player command
	void ReceiveMessage(s_p<CommandMessage> message);

	/// set real coord
	void SetCoord(RealCoord coord);

	/// change entity place on the map
	[[nodiscard]]
	bool SetMapCoord(MapCoord newCoord);

	/// update with time diff
	void Tick(float seconds);

	/// change active task (can be only one)
	void AssignTask(Feature* feature);

	/// add passive task (multiple tasks allowed)
	void AssignPassiveTask(Feature* feature);

	/// return feature, or throw if nothing found
	template<typename F>
	F& Do() { return dynamic_cast<F&>(GetFeature(typeid(F))); }

private:
	Feature& GetFeature(type_index type) const;
	void AddFeature(const string& name, const FeatureInfo* featureInfo);
};
}
