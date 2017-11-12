#ifndef _DEFAULTPLAYERSLOT_H
#define    _DEFAULTPLAYERSLOT_H

#include <PlayerSlot.h>

#include <map>

#include <Strategix_Forward.h>
#include "Sample1_Forward.h"


namespace Sample1
{
using namespace std;
using namespace Strategix;

class DefaultPlayerSlot : public PlayerSlot
{
public:
	void OnAddEnti(s_p<Enti> enti) override {}
	
	void OnRemoveEnti(s_p<Enti> enti) override {}
	
	void OnAddMapResource(s_p<MapResource> mapResource) override {}
	
	void OnRemoveMapResource(s_p<MapResource> mapResource) override {}
	
	void OnChangeResources(s_p<Resources> newResources) override {}
};
}

#endif    /* _DEFAULTPLAYERSLOT_H */

