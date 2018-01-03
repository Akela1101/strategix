#pragma once

#include <Strategix_fwd.h>


namespace strx
{

class Player : boost::noncopyable
{
	const PlayerId playerId;       /// unique id
	const PlayerType type;         /// human | ai
	const int spot;                /// id on map
	const string name;             /// nick or alias
	const string race;             /// race name

	vector<u_p<Entity>> entities;  /// owned enties
	u_p<Resources> resources;      /// available resources amount
	Map& map;                      /// link to map
	u_p<PathFinder> pathFinder;    /// map path finder
	const TechTree& techTree;      /// link to tech tree
	vector<Entity*> entisToRemove; /// entis removed at the end of Tick

public:
	Player(const PlayerMessage& playerMessage, PlayerId playerId, Map& map);
	~Player();

	const string& GetName() const { return name; }
	PlayerType GetType() const { return type; }
	int GetId() const { return spot; }
	Terrain* GetTerrain(MapCoord coord) const;
	u_p<MapObject>& GetMapObject(MapCoord coord) const;
	MapMine* GetMine(MapCoord coord) const;
	const TechTree& GetTechTree() const { return techTree; }

	/// initialize player with entities from map
	void Start();

	/// update player by time
	void Tick(float seconds);

	/// add entity
	void AddEntity(u_p<Entity> entity);

	/// remove entity
	void RemoveEntity(Entity* entity);

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
};
}
