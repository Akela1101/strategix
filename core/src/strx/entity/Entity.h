#pragma once

#include <Strategix_fwd.h>
#include <typeindex>


namespace strx
{

class Entity : boost::noncopyable
{
	Game& game;                  ///< link to game
	Player& player;              ///< link to owner
	const IdType id;             ///< unique id
	const EntityInfo& entiInfo;  ///< link to tree
	RealCoord coord;             ///< real coordinate
	MapCoord mapCoord;           ///< discreet coordinate of object

	using FeaturesType = umap<type_index, u_p<Feature>>;
	FeaturesType features;  ///< set of features

	Feature* task;                  ///< current active feature
	vector<Feature*> passiveTasks;  ///< entity routines like recovery or poison

public:
	Entity(Game& game, Player& player, IdType id, const EntityInfo& entiInfo, RealCoord coord);
	~Entity();

	Game& GetGame() const { return game; }
	Player& GetPlayer() const { return player; }
	const EntityInfo& GetInfo() const { return entiInfo; }
	int GetId() const { return id; }
	RealCoord GetCoord() const { return coord; }
	MapCoord GetMapCoord() const { return mapCoord; }
	HpType GetMaxHp() const;
	HpType GetHp() const;

	/// receive player command
	void ReceiveMessage(s_p<CommandMessage> message);

	/// set real coord
	void SetCoord(RealCoord coord);

	/// change entity place on the map
	[[nodiscard]] bool SetMapCoord(MapCoord newCoord);

	/// update with time diff
	void Tick(float seconds);

	/// change active task (can be only one)
	void AssignTask(Feature* feature);

	/// add passive task (multiple tasks allowed)
	void AssignPassiveTask(Feature* feature);

	/// return feature, or throw if nothing found
	template<typename F> F& Do() const { return dynamic_cast<F&>(GetFeature(typeid(F))); }

private:
	Feature& GetFeature(type_index type) const;
	void AddFeature(const string& name, const FeatureInfo* featureInfo);
};
}  // namespace strx
