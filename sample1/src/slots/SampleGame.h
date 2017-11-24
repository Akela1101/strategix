#ifndef _SAMPLEGAME_H
#define    _SAMPLEGAME_H

#include <strx/kernel/Game.h>
#include <Sample_Forward.h>


namespace sample1
{
using namespace strx;

class GameWidget;

class SampleGame : public Game
{
	umap<string, u_p<SamplePlayerSlot>> playerSlots;
	u_p<GameWidget> gameWidget;

public:
	SampleGame();
	~SampleGame() override;
	
	void Start();
	
private:
	void PlaceEntis();
};

}

#endif    /* _SAMPLEGAME_H */

