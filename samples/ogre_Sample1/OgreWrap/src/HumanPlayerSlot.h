/* 
 * File:   HumanPlayerSlot.h
 * Author: Akela1101
 *
 * Created on 13 Январь 2011 г., 21:23
 */

#ifndef _HUMANPLAYERSLOT_H
#define	_HUMANPLAYERSLOT_H

#include <PlayerSlot.h>

#include <MyGUI.h>
#include <map>

#include <Strategix_Forward.h>
#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

	class HumanPlayerSlot : public PlayerSlot
	{		
		sh_p<MyGUI::Gui> myGUI;		
		MyGUI::StaticText *resourcesText;

	protected:
		std::map<sh_p<Enti>, sh_p<OObjectEntiSlot> > entiSlots;
		std::map<sh_p<MapResource>, sh_p<OObjectResource> > resources;

	public:
		HumanPlayerSlot();
		~HumanPlayerSlot();

		virtual void OnAddEnti(sh_p<Enti> enti);
		virtual void OnRemoveEnti(sh_p<Enti> enti);
		virtual void OnAddMapResource(sh_p<MapResource> mapResource);
		virtual void OnRemoveMapResource(sh_p<MapResource> mapResource);
		virtual void OnChangeResources(sh_p<Resources> newResources);
	};
}

#endif	/* _HUMANPLAYERSLOT_H */

