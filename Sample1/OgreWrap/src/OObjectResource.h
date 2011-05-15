/* 
 * File:   OObjectResource.h
 * Author: Akela1101
 *
 * Created on 13 Май 2011 г., 18:39
 */

#ifndef _OOBJECTRESOURCE_H
#define	_OOBJECTRESOURCE_H

#include "OObject.h"

#include "CoordStructs.h"
#include "Map.h"


namespace Sample1
{
	using namespace std;
	using namespace Ogre;
	using namespace Strategix;

	class OObjectResource : public OObject
	{
	protected:
		sh_p<Map::Resource> resource;

	public:
		OObjectResource(const std::string &meshName, const RealCoord &coord);
		virtual ~OObjectResource() {}

	};
}

#endif	/* _OOBJECTRESOURCE_H */

