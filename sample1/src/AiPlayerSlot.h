#ifndef _AIPLAYERSLOT_H
#define    _AIPLAYERSLOT_H

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
	//std::map<s_p<Enti>, s_p<OObjectEntiSlot>> entiSlots;

public:
	void OnAddEnti(s_p<Enti> enti) override;
	void OnRemoveEnti(s_p<Enti> enti) override;
	
	void OnAddMapResource(s_p<MapResource> mapResource) override {}
	
	void OnRemoveMapResource(s_p<MapResource> mapResource) override {}
	
	void OnChangeResources(s_p<Resources> newResources) override {}
};
}

#endif    /* _AIPLAYERSLOT_H */

