/* 
 * File:   AiPlayerSlot.h
 * Author: Akela1101
 *
 * Created on 13 Июль 2011 г., 16:34
 */

#ifndef _AIPLAYERSLOT_H
#define	_AIPLAYERSLOT_H

#include <PlayerSlot.h>

#include <map>

#include <Strategix_Forward.h>
#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

	class AiPlayerSlot : public PlayerSlot
	{
	protected:
		std::map<sh_p<Enti>, sh_p<OObjectEntiSlot> > entiSlots;

	public:
		virtual void OnAddEnti(sh_p<Enti> enti);
		virtual void OnRemoveEnti(sh_p<Enti> enti);
		virtual void OnAddMapResource(sh_p<MapResource> mapResource) {}
		virtual void OnRemoveMapResource(sh_p<MapResource> mapResource) {}
		virtual void OnChangeResources(sh_p<Resources> newResources) {}
	};
}

#endif	/* _AIPLAYERSLOT_H */

