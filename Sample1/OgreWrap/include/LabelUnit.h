/* 
 * File:   LabelUnit.h
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 11:49
 */

#ifndef _LABELUNIT_H
#define	_LABELUNIT_H

#include "EntityUnit.h"
#include "GameStructs.h"

namespace Sample1
{
	using namespace Ogre;
	
	class LabelUnit : public EntityUnit
	{
	protected:

	public:
		LabelUnit(const Strategix::MapCoord &mapCoord, const String &title);
		virtual ~LabelUnit();
		void Update();
		void SetColor(const ColourValue& color);
		void Show(bool isShow);
	};
}

#endif	/* _LABELUNIT_H */

