#ifndef _PLAYERSLOT_H
#define    _PLAYERSLOT_H

#include "Strategix_Forward.h"


namespace Strategix
{
class PlayerSlot
{
public:
	PlayerSlot() = default;
	virtual ~PlayerSlot() = default;
	
	virtual void OnAddEnti(s_p<Enti> enti) = 0;
	virtual void OnRemoveEnti(s_p<Enti> enti) = 0;
	virtual void OnAddMapResource(s_p<MapResource> mapResource) = 0;
	virtual void OnRemoveMapResource(s_p<MapResource> mapResource) = 0;
	virtual void OnChangeResources(s_p<Resources> newResources) = 0;
	
	PlayerSlot(const PlayerSlot& _c) = delete;
	PlayerSlot& operator=(const PlayerSlot& _c) = delete;
};
}

#endif    /* _PLAYERSLOT_H */

