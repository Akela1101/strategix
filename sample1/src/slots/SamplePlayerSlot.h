#ifndef _SAMPLEPLAYERSLOT_H
#define    _SAMPLEPLAYERSLOT_H

#include <strx/player/PlayerSlot.h>
#include <Sample_Forward.h>


namespace sample1
{
using namespace std;
using namespace strx;

class SampleEntiSlot;

class SamplePlayerSlot : public PlayerSlot
{
	using PlayerSlot::PlayerSlot;
	
	umap<int, u_p<SampleEntiSlot>> entiSlots;
	
public:
	SampleEntiSlot& GetEntity(int id) { return *entiSlots[id].get(); }
	void EntiAdded(Enti* enti) override;
	void EntiRemoved(Enti* enti) override {}
	void ResourcesChanged(Resources* newResources) override {}
};
}

#endif    /* _SAMPLEPLAYERSLOT_H */

