#ifndef _PLAYER_H
#define    _PLAYER_H

#include <Strategix_Forward.h>


namespace strx
{

class Player : boost::noncopyable
{
	PlayerSlot* slot = nullptr;    /// callback class
	const string name;
	const PlayerType type;
	const int id;
	const string raceName;
	
	vector<u_p<Entity>> entities;  /// owned enties
	u_p<Resources> resources;      /// available resources amount
	Map& map;                      /// link to map
	u_p<PathFinder> pathFinder;    /// map path finder
	const TechTree& techTree;      /// link to tech tree
	vector<Entity*> entisToRemove; /// entis removed at the end of Tick

public:
	Player(const string& name, PlayerType type, int id, const string& raceName, Map& map);
	~Player();
	
	const string& GetName() const { return name; }
	PlayerType GetType() const { return type; }
	int GetId() const { return id; }
	Map& GetMap() const { return map; } //TODO: remove
	Terrain* GetTerrain(MapCoord coord) const;
	u_p<MapObject>& GetMapObject(MapCoord coord) const;
	MapMine* GetMine(MapCoord coord) const;
	const TechTree& GetTechTree() const { return techTree; }
	void SetSlot(PlayerSlot* slot);
	
	/// initialize player with entities from map
	void Start();
	
	/// update player by time
	void Tick(float seconds);
	
	/// add entity
	void AddEntity(Entity* entity);
	
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

#endif    /* _PLAYER_H */

