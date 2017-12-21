#pragma once

#include <strx/kernel/GameSlot.h>
#include <Sample_fwd.h>

namespace sample1
{
class SampleGame : public GameSlot
{
	umap<string, u_p<SamplePlayer>> playerSlots;
	u_p<SampleGameWidget> gameWidget;
	SampleMapWidget* mapWidget;

public:
	static void Configure();
	
	SampleGame();
	~SampleGame() override;
	
	void Start();
	
	void PlayerAdded(Player* player) override;

private:
	void InitHuman(SamplePlayer* playerSlot);
};

}
