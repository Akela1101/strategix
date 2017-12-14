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
	
	SampleMapWidget* mapWidget = nullptr;
	umap<int, u_p<SampleEntiSlot>> entiSlots;
	
public:
	SampleEntiSlot& GetEntitySlot(int id) { return *entiSlots[id].get(); }
	void SetMapWidget(SampleMapWidget* mapWidget) { this->mapWidget = mapWidget; }
	
	void EntiAdded(Entity* entity) override;
	void EntiRemoved(Entity* entity) override {}
	void ResourcesChanged(Resources* newResources) override {}
};
}

#endif    /* _SAMPLEPLAYERSLOT_H */

