#include <slots/SampleEntiSlot.h>
#include <slots/SamplePlayerSlot.h>
#include <Strategix.h>

#include "SampleGame.h"

namespace sample1
{
using namespace strx;

void SampleGame::Init()
{
	// initialize map and players
	Kernel::LoadMap("1x1");
	
	auto inu = new SamplePlayerSlot("Inu", PlayerType::HUMAN, 0, "Spher");
	inu->AddEnti(new SampleEntiSlot("Spher_Worker"));
	
	auto saru = new SamplePlayerSlot("Saru", PlayerType::AI, 1, "Spher");
	saru->AddEnti(new SampleEntiSlot("Spher_Worker"));
	
	Kernel::AddPlayer(inu);
	Kernel::AddPlayer(saru);
}

}
