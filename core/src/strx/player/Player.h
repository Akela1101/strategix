#pragma once

#include <Strategix_fwd.h>


namespace strx
{

class Player : boost::noncopyable
{
	Game& game;             ///< link to game
	const PlayerId id;      ///< unique id
	const PlayerType type;  ///< human | ai
	const int spot;         ///< id on map
	const string name;      ///< nick or alias
	const string race;      ///< race name

	umap<IdType, s_p<Entity>> entities;  ///< owned entities
	u_p<Resources> resources;            ///< available resources amount
	Map& map;                            ///< link to map
	u_p<PathFinder> pathFinder;          ///< map path finder
	const TechTree& techTree;            ///< link to tech tree

public:
	Player(Game& game, PlayerId id, const PlayerMessage& playerMessage, Map& map);
	~Player();

	Game& GetGame() const { return game; }
	PlayerType GetType() const { return type; }
	int GetSpot() const { return spot; }
	const string& GetName() const { return name; }
	s_p<Entity> GetEntity(IdType id) const;
	Terrain* GetTerrain(MapCoord coord) const;
	u_p<MapObject>& GetMapObject(MapCoord coord) const;
	MapMine* GetMine(MapCoord coord) const;
	const TechTree& GetTechTree() const { return techTree; }

	/// initialize player with entities from map
	void Start();

	/// entity added to game
	void EntityAdded(s_p<Entity> entity);

	/// remove entity
	void EntityRemoved(IdType id);

	/// add resource to disposal
	void AddResource(const Resource& deltaResource);

	/// find nearest resource collector building
	Entity* FindCollector(MapCoord coord) const;

	/// find nearest mine in the given manh radius
	MapMine* FindMine(MapCoord coord, string resourceName, int squareRadius) const;

	/// find path to a circle with the given radius
	u_p<MapPath> FindPath(MapCoord from, MapCoord till, float radius) const;

	/// pick resource from the mine and change it accordingly
	ResourceUnit PickResource(MapMine* mine, ResourceUnit amount);

private:
	void ObjectRemoved(IdType id, MapCoord coord);
};
}  // namespace strx
