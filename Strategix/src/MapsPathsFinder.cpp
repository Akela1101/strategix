/* 
 * File:   MapsPathsFinder.cpp
 * Author: Akela1101
 * 
 * Created on 24 Март 2011 г., 17:14
 */

#include "MapsPath.h"
#include "Map.h"

#include "MapsPathsFinder.h"


namespace Strategix
{

MapsPathsFinder::MapsPathsFinder(const Map &map)
	:
	map(map)
{
}

MapsPathsFinder::~MapsPathsFinder()
{
}

sh_p<MapsPath> MapsPathsFinder::FindPath(const MapCoord from, const MapCoord till)
{
	sh_p<MapsPath> mapsPath;

	if( from.x == till.x && from.y == till.y )
		return mapsPath;

	static const MapCoord around[8] =
	{
		MapCoord(-1,  1), MapCoord( 0, 1), MapCoord( 1, 1),
		MapCoord(-1,  0), MapCoord( 1,-1), MapCoord( 1, 0),
		MapCoord(-1, -1), MapCoord( 0,-1) // <^ done for ability % 2
	};

	list<sh_p<CellPrice> > opened, closed;
	sh_p<CellPrice> current = sh_p<CellPrice>(new CellPrice(from, 0, 0, 0));

	opened.push_back(current);

	while( !opened.empty() )
	{
		list<sh_p<CellPrice> > ::iterator it_min, it = opened.begin();
		it_min = it++; // it_min == begin, it == begin + 1
		Price F_min = (*it_min)->F;

		for( ; it != opened.end(); ++it )
		{
			if( F_min > (*it)->F )
			{
				it_min = it;
				F_min = (*it)->F;
			}
		}
		current = *it_min;	
		opened.erase(it_min);	
		closed.push_front(current);

		if( current->mc == till ) // Way's found !
		{
			// Return list
			for( CellPrice *cellPrice = current.get(); cellPrice; cellPrice = cellPrice->parent )
			{
				mapsPath->PushFront(cellPrice->mc);
			}
			break;
		}

		for( int i = 0; i < 8; ++i )
		{
			MapCoord checking_mc = current->mc + around[i];

			if( map.IsCell(checking_mc) && !GetByCoord(closed, checking_mc).get() && IsAccessible(checking_mc) )
			{
				// map(current->mc) @#~
				Price new_G = current->G + ((i % 2) ? 10 : 14) * map(current->mc).retard; // sqrt(2)*10, 10

				sh_p<CellPrice> openedCell = GetByCoord(opened, checking_mc);
				if( !openedCell.get() )
				{
					const int new_H = Distance(openedCell->mc, till);
					openedCell.reset(new CellPrice(checking_mc, current.get(), new_G, new_H));
					opened.push_back(openedCell);
				}
				else
				{
					// in open list & mark < old mark
					if( openedCell->G > new_G )
					{
						openedCell->parent = current.get();
						openedCell->G = new_G;
						openedCell->F = openedCell->G + openedCell->H;
					}
				}
			}
		}
	}

	return mapsPath;
}

}
