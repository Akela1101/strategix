#ifndef _MAPLOCAL_H
#define    _MAPLOCAL_H

#include "Map.h"

#include "Strategix_Forward.h"


namespace strategix
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
	
	float PickResource(Mine* mine, float amount) override;
	void RemoveMine(Mine* mine);
};
}

#endif    /* _MAPLOCAL_H */

