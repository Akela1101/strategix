#ifndef _SAMPLEGAME_H
#define    _SAMPLEGAME_H

#include <strx/kernel/Game.h>
#include <Sample_Forward.h>

namespace sample1
{
using namespace strx;

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
};

}

#endif    /* _SAMPLEGAME_H */

