#pragma once

#include <strx/kernel/Game.h>
#include <Sample_Forward.h>

namespace sample1
{
class SampleGame : public Game
{
	umap<string, u_p<SamplePlayerSlot>> playerSlots;
	u_p<SampleGameWidget> gameWidget;
	SampleMapWidget* mapWidget;

public:
	static void Configure();
	
	SampleGame();
	~SampleGame() override;
	
	void Start() override;
	
	void PlayerAdded(Player* player) override;

private:
	void InitHuman(SamplePlayerSlot* playerSlot);
};

}
