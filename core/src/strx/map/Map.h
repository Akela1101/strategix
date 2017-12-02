#ifndef _MAP_H
#define _MAP_H

#include <strx/map/BaseMap.h>

namespace strx
{

class Map : public BaseMap
{
	Player& player;                   /// owner
	u_p<MapsPathsFinder> pathsFinder; /// path finder
	
public:
	Map(const BaseMap& map, Player& player);
	~Map() override;
	
	u_p<MapsPath> FindPath(MapCoord from, MapCoord till) const;
	ResourceUnit PickResource(Mine* mine, ResourceUnit amount);
	void RemoveMine(Mine* mine);
};
}

#endif    /* _MAP_H */

