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
#include "Interfaces.h"

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

	class OObjectUnit : public OObject, public Unit
	{
	protected:
		AnimationState *animationState;
		std::map<string, sh_p<AnimationState> > animationStates;

	public:
		OObjectUnit(Enti *enti);
		virtual ~OObjectUnit() {}

		virtual void OnTick(const float seconds);
		virtual void OnMoveStart();
		virtual void OnMove();
		virtual void OnMoveStop();
	};
}

#endif	/* _OOBJECTUNIT_H */

