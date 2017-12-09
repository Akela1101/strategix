#include "MapPath.h"
#include "Map.h"

#include "MapPathFinder.h"


namespace strx
{
static const int epsilon = 3;
static const int straight = 10;
static const int diagonal = straight * M_SQRT2;
static const MapCoord around[8] =
		{
				MapCoord(-1,  1), MapCoord(0,  1), MapCoord(1,  1),
				MapCoord(-1,  0), MapCoord(1, -1), MapCoord(1,  0),
				MapCoord(-1, -1), MapCoord(0, -1)  // i % 2 ? straight : diagonal
		};

using Price = int;
struct CellPrice
{
	MapCoord coord;
	CellPrice* parent;
	Price F, G, H;
	
	CellPrice(MapCoord coord, CellPrice* parent, Price G, Price H)
			: coord(coord), parent(parent), F(G + H), G(G), H(H) {}
};

Price Distance(const MapCoord& a, const MapCoord& b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y)) * epsilon;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MapPathFinder::MapPathFinder(const Map& map)
		: map(map) {}

u_p<MapPath> MapPathFinder::FindPath(const MapCoord from, const MapCoord till) const
{
	// cannot be achieved
	if (!IsAccessible(till)) return nullptr;
	
	// already on place
	if (from.x == till.x && from.y == till.y) return nullptr;
	
	umap<MapCoord, u_p<CellPrice>> opened, closed;
	opened.emplace(from, new CellPrice(from, nullptr, 0, 0));
	
	auto mapsPath = make_u<MapPath>();
	while (!opened.empty())
	{
		auto itMin = min_element(all_(opened), [](auto& a, auto& b) { return a.second->F < b.second->F; });
		CellPrice* current = itMin->second.get();
		
		closed.emplace(current->coord, move(itMin->second));
		opened.erase(itMin);
		
		if (current->coord == till) // way found !
		{
			for (CellPrice* cellPrice = current; cellPrice; cellPrice = cellPrice->parent)
			{
				mapsPath->AddPoint(cellPrice->coord);
			}
			mapsPath->TakeNext(); // remove first
			break;
		}
		
		for (int i = 0; i < 8; ++i)
		{
			MapCoord coord = current->coord + around[i];
			
			if (IsAccessible(coord) && !in_(coord, closed))
			{
				Price nextG = current->G + (i % 2 ? straight : diagonal) / map.GetCell(coord).terrain->quality;
				
				auto it = opened.find(coord);
				if (it == opened.end())
				{
					Price nextH = Distance(coord, till);
					CellPrice* next = new CellPrice(coord, current, nextG, nextH);
					opened.emplace(coord, next);
				}
				else if (it->second->G > nextG) // in open list & current distance > new distance
				{
					CellPrice* next = it->second.get();
					next->parent = current;
					next->G = nextG;
					next->F = next->G + next->H;
				}
			}
		}
	}
	//trace_log << "Checked tiles: " << closed.size();
	return mapsPath;
}

bool MapPathFinder::IsAccessible(const MapCoord& coord) const
{
	return map.IsCell(coord) && map.GetCell(coord).terrain->quality > 0;
}

}
