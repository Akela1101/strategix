/* 
 * File:   OObjectResource.h
 * Author: Akela1101
 *
 * Created on 13 Май 2011 г., 18:39
 */

#ifndef _OOBJECTRESOURCE_H
#define	_OOBJECTRESOURCE_H

#include "OObject.h"

#include <MapResource.h>
#include <Ogre.h>
#include <string>

#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

	class OObjectResource : public OObject
	{
	public:
		sh_p<MapResource> mapResource;

	public:
		OObjectResource(const string meshName, sh_p<MapResource> mapResource)
			:
			OObject(meshName),
			mapResource(mapResource)
		{
			entity->setUserAny(Any(this)); // Link from Entity
			entity->setQueryFlags(RES_MASK); // Mask for mouse selection

			RealCoord resourceCoord = mapResource->mapCoord; // convert to float
			node->setPosition(resourceCoord.x, 0, resourceCoord.y);
		}
		virtual ~OObjectResource() {}
	};
}

#endif	/* _OOBJECTRESOURCE_H */

