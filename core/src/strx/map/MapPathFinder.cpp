#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

#include "MapPath.h"
#include "Map.h"

#include "MapPathFinder.h"


namespace strx
{
static const int maxCheckedTiles = 300;
static const int epsilon = 4;
static const int straight = 10;
static const int diagonal = straight * M_SQRT2;
static const MapCoord around[8] =
		{
				MapCoord(-1,  1), MapCoord(0,  1), MapCoord(1,  1),
				MapCoord(-1,  0), MapCoord(1, -1), MapCoord(1,  0),
				MapCoord(-1, -1), MapCoord(0, -1)  // i % 2 ? straight : diagonal
		};

using Price = int;
struct PricedCell
{
	MapCoord coord;
	PricedCell* parent;
	Price F, G, H;
	
	PricedCell(MapCoord coord, PricedCell* parent, Price G, Price H)
			: coord(coord), parent(parent), F(G + H), G(G), H(H) {}
};

Price Distance(const MapCoord& a, const MapCoord& b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y)) * epsilon;
}

// opened cells are retrievable by coordinate and sorted by price
using namespace boost::multi_index;
using OpenedCellsType = multi_index_container<u_p<PricedCell>, indexed_by
		< hashed_unique<member<PricedCell, MapCoord, &PricedCell::coord>, hash<MapCoord>>
		, ordered_non_unique<tag<Price>, member<PricedCell, Price, &PricedCell::F>>
		>>;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MapPathFinder::MapPathFinder(const Map& map)
		: map(map) {}

u_p<MapPath> MapPathFinder::FindPath(MapCoord from, MapCoord till, float radius) const
{
	// already on place
	if ((from - till).Len() <= radius) return make_u<MapPath>();
	
	OpenedCellsType opened;
	umap<MapCoord, u_p<PricedCell>> closed;
	
	PricedCell* closest = new PricedCell(from, nullptr, 0, Distance(from, till)); // closest to till by heuristic
	opened.emplace(closest);
	bool isFound = false;
	for (int k = 0; k < maxCheckedTiles && !opened.empty(); ++k)
	{
		auto& openedByPrice = opened.get<Price>();
		auto itMin = openedByPrice.begin(); // get cell with minimum Price
		PricedCell* current = itMin->get();
		
		// move this cell from opened to closed
		closed.emplace(current->coord, move(const_cast<u_p<PricedCell>&>(*itMin)));
		openedByPrice.erase(itMin);
		
		if ((current->coord - till).Len() <= radius) // way found !
		{
			closest = current;
			isFound = true;
			break;
		}
		
		for (int i = 0; i < 8; ++i)
		{
			MapCoord coord = current->coord + around[i];
			float currentQuality = map.GetCell(current->coord).terrain->quality;
			
			if (IsAccessible(coord) && !in_(coord, closed))
			{
				float quality = 0.5 * (currentQuality + map.GetCell(coord).terrain->quality);
				Price nextG = current->G + (i % 2 ? straight : diagonal) / quality;
				
				auto it = opened.find(coord);
				if (it == opened.end())
				{
					Price nextH = Distance(coord, till);
					PricedCell* next = new PricedCell(coord, current, nextG, nextH);
					if (nextH < closest->H) closest = next;
					
					opened.emplace(next);
				}
				else if ((*it)->G > nextG) // in open list & current distance > new distance
				{
					opened.modify(it, [current, nextG](auto& next)
					{
						next->parent = current;
						next->G = nextG;
						next->F = nextG + next->H;
					});
				}
			}
		}
	}
	trace_log << "Checked tiles: " << closed.size();
	return GetWay(closest, isFound);
}

bool MapPathFinder::IsAccessible(const MapCoord& coord) const
{
	if (!map.IsCell(coord)) return false;
	
	auto& cell = map.GetCell(coord);
	return cell.terrain->quality > 0 && !cell.object;
}

u_p<MapPath> MapPathFinder::GetWay(PricedCell* cell, bool isFound) const
{
	auto mapsPath = make_u<MapPath>(isFound);
	for (; cell; cell = cell->parent)
	{
		mapsPath->AddPoint(cell->coord);
	}
	mapsPath->TakeNext(); // remove first
	return mapsPath;
}

}
