/* 
 * File:   MapsPath.h
 * Author: Akela1101
 *
 * Created on 24 Март 2011 г., 17:13
 */

#ifndef _MAPSPATH_H
#define	_MAPSPATH_H

#include <deque>

#include "Strategix_Forward.h"


namespace Strategix
{
	class MapsPath
	{
		std::deque<MapCoord> path; // vector ???

	public:
		MapsPath() {}
		bool IsEmpty() { return path.empty(); }
		MapCoord PickFront()
		{
			MapCoord frontCoord = path.back();
			path.pop_back();
			return frontCoord;
		}
		void PushFront(const MapCoord mapCoord) { path.push_back(mapCoord); }

	private:
		MapsPath(const MapsPath &_c);
		MapsPath& operator =(const MapsPath &_c);
	};
}

#endif	/* _MAPSPATH_H */

