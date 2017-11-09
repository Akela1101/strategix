/* 
 * File:   OObjectEntiSlot.h
 * Author: Akela1101
 *
 * Created on 18 Март 2011 г., 15:58
 */

#ifndef _OOBJECTENTISLOT_H
#define	_OOBJECTENTISLOT_H

#include "OObjectTitled.h"

#include <EntiSlot.h>
#include <Ogre.h>
#include <map>
#include <string>

#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace Ogre;
	using namespace Strategix;	

	class OObjectEntiSlot : public OObjectTitled, public EntiSlot
	{
	protected:
		AnimationState *animationState;
		std::map<string, sh_p<AnimationState> > animationStates;

	public:
		OObjectEntiSlot(sh_p<Enti> enti);

		virtual void OnTick(const float seconds);
		virtual void OnMoveStart();
		virtual void OnMove();
		virtual void OnMoveStop();
		virtual void OnHpChange();
	};
}

#endif	/* _OOBJECTENTISLOT_H */

