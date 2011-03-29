/* 
 * File:   MapsPathsFinder.h
 * Author: Akela1101
 *
 * Created on 24 Март 2011 г., 17:14
 */

#ifndef _MAPSPATHSFINDER_H
#define	_MAPSPATHSFINDER_H

#include "Map.h"

#include "Nya.hpp"


namespace Strategix
{
	class MapsPath;

	class MapsPathsFinder
	{
		struct CellPrice
		{
			MapCoord mc;
			typedef int Price;
			Price F, G, H;
			CellPrice *parent;
		};

		mutable CellPrice **priceCells;

	public:
		MapsPathsFinder();
		virtual ~MapsPathsFinder();

		sh_p<MapsPath> FindPath(const MapCoord from, const MapCoord till);
		//sh_p<MapsPath> FindPath_Debug(const MapCoord from, const MapCoord till, list<Cell*> *&p_closed);

	private:
		MapsPathsFinder(const MapsPathsFinder &_c);
		MapsPathsFinder & operator =(const MapsPathsFinder &_c);

//		bool IsIn(const list<Cell*> &list, const Cell *cell) const;
//		bool IsAccessible(const MapCoord &mc) const;
//		int Distance(const MapCoord &a, const MapCoord &b) const;
	};
}
#endif	/* _MAPSPATHSFINDER_H */

