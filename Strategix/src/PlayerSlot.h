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
		
		virtual void OnAddEnti(sh_p<Enti> enti) = 0;
		virtual void OnRemoveEnti(sh_p<Enti> enti) = 0;
		virtual void OnAddMapResource(sh_p<MapResource> mapResource) = 0;
		virtual void OnRemoveMapResource(sh_p<MapResource> mapResource) = 0;
		virtual void OnChangeResources(sh_p<Resources> newResources) = 0;

	private:
		PlayerSlot(const PlayerSlot &_c);
		PlayerSlot & operator =(const PlayerSlot &_c);
	};
}

#endif	/* _PLAYERSLOT_H */

