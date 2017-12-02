#ifndef _MAPSPATHSFINDER_H
#define    _MAPSPATHSFINDER_H

#include <list>

#include "Strategix_Forward.h"


namespace strx
{
class MapsPathsFinder
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
	MapsPathsFinder(const Map& map);
	
	virtual ~MapsPathsFinder() = default;
	
	virtual u_p<MapsPath> FindPath(MapCoord from, MapCoord till) const;

private:
	MapsPathsFinder(const MapsPathsFinder& _c);
	MapsPathsFinder& operator =(const MapsPathsFinder& _c);
	
	s_p<CellPrice> GetByCoord(list <s_p<CellPrice>>& list, MapCoord checking_mc) const;
	bool IsAccessible(const MapCoord& mc) const;
	
	// Change magic 10 !!!!
	int Distance(const MapCoord& a, const MapCoord& b) const { return (abs(a.x - b.x) + abs(a.y - b.y)) * 10; }
};
}
#endif    /* _MAPSPATHSFINDER_H */

