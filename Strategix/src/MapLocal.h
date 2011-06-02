/* 
 * File:   MapLocal.h
 * Author: Akela1101
 *
 * Created on 24 Март 2011 г., 14:02
 */

#ifndef _MAPLOCAL_H
#define	_MAPLOCAL_H

#include "Map.h"

#include "Strategix_Forward.h"


namespace Strategix
{
	using namespace std;

	class MapLocal : public Map
	{
		MapFull *mapFull; // For pushing synchronizing calls
		sh_p<MapsPathsFinder> pathsFinder;
		
	public:
		MapLocal(MapFull *mapFull);
		virtual ~MapLocal();

		sh_p<MapsPath> FindPath(const MapCoord from, const MapCoord till);

	private:
		MapLocal(const MapLocal &_c);
		MapLocal & operator =(const MapLocal &_c);
	};
}

#endif	/* _MAPLOCAL_H */

