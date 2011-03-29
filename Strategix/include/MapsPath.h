/* 
 * File:   MapsPath.h
 * Author: Akela1101
 *
 * Created on 24 Март 2011 г., 17:13
 */

#ifndef _MAPSPATH_H
#define	_MAPSPATH_H

#include "CoordStructs.h"

#include <deque>


namespace Strategix
{
	class MapsPath
	{
		std::deque<MapCoord> way;

	public:
		MapsPath();		
		virtual ~MapsPath();

		bool IsEmpty() { return way.empty(); }
		MapCoord PickFront()
		{
			MapCoord frontCoord = way.front();
			way.pop_front();
			return frontCoord;
		}
		void PutBack(const MapCoord mapCoord) { way.push_back(mapCoord); }

	private:
		MapsPath(const MapsPath &_c);
		MapsPath& operator =(const MapsPath &_c);
	};
}

#endif	/* _MAPSPATH_H */

