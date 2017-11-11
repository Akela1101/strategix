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
	const MapCoord GetInitialPostion() const { return initialPosition; }
	
	s_p<MapsPath> FindPath(const MapCoord from, const MapCoord till);
	
	float PickResource(s_p<MapResource> mapResource, const float amount);
	void RemoveMapResource(s_p<MapResource> mapResource);

private:
	MapLocal(Player* player, MapFull* mapFull);
	MapLocal(const MapLocal& _c);
	MapLocal& operator=(const MapLocal& _c);
};
}

#endif    /* _MAPLOCAL_H */

