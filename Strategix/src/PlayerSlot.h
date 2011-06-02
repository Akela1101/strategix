/* 
 * File:   PlayerSlot.h
 * Author: Akela1101
 *
 * Created on 17 Март 2011 г., 20:18
 */

#ifndef _PLAYERSLOT_H
#define	_PLAYERSLOT_H

#include "Strategix_Forward.h"


namespace Strategix
{
	class PlayerSlot
	{
	public:
		PlayerSlot() {}
		virtual ~PlayerSlot() {}
		
		virtual void OnAddEnti(Enti *enti) = 0;
		virtual void OnChangeResources(const Resources &newResources) = 0;

	private:
		PlayerSlot(const PlayerSlot &_c);
		PlayerSlot & operator =(const PlayerSlot &_c);
	};
}

#endif	/* _PLAYERSLOT_H */

