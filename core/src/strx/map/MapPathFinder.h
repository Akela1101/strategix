#ifndef _MAPPATHFINDER_H
#define _MAPPATHFINDER_H

#include <list>

#include "Strategix_Forward.h"


namespace strx
{
class MapPathFinder
{
	typedef int Price;
	
	struct CellPrice
	{
		MapCoord mc;
		CellPrice* parent;
		Price F, G, H;
		
		CellPrice(MapCoord mc, CellPrice* parent, Price G, Price H)
				: mc(mc), parent(parent), F(G + H), G(G), H(H) {}
	};

public:
	const Map& map;

public:
	MapPathFinder(const Map& map);
	virtual ~MapPathFinder() = default;
	
	virtual u_p<MapPath> FindPath(MapCoord from, MapCoord till) const;

private:
	MapPathFinder(const MapPathFinder& _c);
	MapPathFinder& operator =(const MapPathFinder& _c);
	
	s_p<CellPrice> GetByCoord(list <s_p<CellPrice>>& list, MapCoord checking_mc) const;
	bool IsAccessible(const MapCoord& mc) const;
	
	// Change magic 10 !!!!
	int Distance(const MapCoord& a, const MapCoord& b) const { return (abs(a.x - b.x) + abs(a.y - b.y)) * 10; }
};
}
#endif //_MAPPATHFINDER_H

