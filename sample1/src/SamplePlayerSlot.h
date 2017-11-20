#ifndef _SAMPLEPLAYERSLOT_H
#define    _SAMPLEPLAYERSLOT_H

#include <strx/player/PlayerSlot.h>
#include <Sample1_Forward.h>


namespace sample1
{
using namespace std;
using namespace strx;

class SamplePlayerSlot : public PlayerSlot
{
	using PlayerSlot::PlayerSlot;
	
public:
	void OnAddEnti(EntiSlot* enti) override {}
	
	void OnRemoveEnti(EntiSlot* enti) override {}
	
	void OnAddMine(Mine* mine) override {}
	
	void OnRemoveMine(Mine* mine) override {}
	
	void OnChangeResources(Resources* newResources) override {}
};
}

#endif    /* _SAMPLEPLAYERSLOT_H */

