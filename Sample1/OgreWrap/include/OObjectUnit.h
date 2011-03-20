/* 
 * File:   OObjectUnit.h
 * Author: Akela1101
 *
 * Created on 18 Март 2011 г., 15:58
 */

#ifndef _OOBJECTUNIT_H
#define	_OOBJECTUNIT_H

#include "OObject.h"

#include "Unit.h"
#include "CoordStructs.h"

#include <OgrePrerequisites.h>
#include <OgreVector3.h>


namespace Sample1
{
	using namespace Strategix;
	using namespace Ogre;

	class OObjectUnit : public Strategix::Unit, public OObject
	{
	protected:
		Real distance; // The distance the object has left to travel
		Vector3 direction; // The direction the object is moving
		Vector3 destination; // The destination the object is moving towards

	public:
		OObjectUnit(Enti *enti);
		virtual ~OObjectUnit();

		virtual void OnTick(float time);

		void AddWayTo(Vector3 &pos); // Mouse pointer intersection with earth
		void AddWayTo_Debug(Vector3 &pos);

	protected:		
		MapCoord GetMapCoord(const Vector3 &pos);
		Vector3 GetDiscretePos(const MapCoord &mapCoord);
		Vector3 GetDiscretePos(const Vector3 &pos);
	};
}

#endif	/* _OOBJECTUNIT_H */

