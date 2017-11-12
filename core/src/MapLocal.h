#ifndef _MAPLOCAL_H
#define    _MAPLOCAL_H

#include "Map.h"

#include "Strategix_Forward.h"


namespace Strategix
{
using namespace std;

class MapLocal : public Map
{
	friend class MapFull;
	
	Player* player; // owner
	MapFull* mapFull; // For pushing synchronizing calls
	MapCoord initialPosition; // of player
	s_p<MapsPathsFinder> pathsFinder;

public:
	MapLocal(Player* player, MapFull* mapFull);
	MapLocal(const MapLocal& _c) = delete;
	MapLocal& operator=(const MapLocal& _c) = delete;
	
	const MapCoord GetInitialPostion() const { return initialPosition; }
	
	s_p<MapsPath> FindPath(MapCoord from, MapCoord till) const;
	
	float PickResource(s_p<MapResource>& mapResource, float amount) override;
	void RemoveMapResource(s_p<MapResource>& mapResource);
};
}

#endif    /* _MAPLOCAL_H */

