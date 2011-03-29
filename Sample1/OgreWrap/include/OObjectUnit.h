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

#include <map>
#include <string>

#include "Nya.hpp"


namespace Sample1
{
	using namespace std;
	using namespace Ogre;
	using namespace Strategix;	

	class OObjectUnit : public Strategix::Unit, public OObject
	{
	protected:
		AnimationState *animationState;
		std::map<string, sh_p<AnimationState> > animationStates;

	public:
		OObjectUnit(Enti *enti);
		virtual ~OObjectUnit();

		virtual void OnTick(const float seconds);
		virtual void OnMoveStart();
		virtual void OnMove(const RealCoord newCoord);
		virtual void OnMoveStop();

	};
}

#endif	/* _OOBJECTUNIT_H */

