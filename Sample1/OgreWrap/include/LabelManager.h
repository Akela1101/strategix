/* 
 * File:   LabelManager.h
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 11:49
 */

#ifndef _LABELMANAGER_H
#define	_LABELMANAGER_H

#include "EntityManager.h"
#include "GameStructs.h"

namespace Sample1
{
	using namespace Ogre;
	
	class LabelManager : public EntityManager
	{
	protected:

	public:
		LabelManager(const Strategix::MapCoord &mapCoord, const String &title);
		virtual ~LabelManager();
		void Update();
		void SetColor(const ColourValue& color);
		void Show(bool isShow);
	};
}

#endif	/* _LABELMANAGER_H */

