#include <boost/range/irange.hpp>
#include <graphics/GameWidget.h>
#include <strx/player/Player.h>
#include <slots/SampleEntiSlot.h>
#include <slots/SamplePlayerSlot.h>
#include <Strategix.h>
#include <MapAreaWidget.h>
#include <MapInfo.h>

#include "SampleGame.h"


namespace sample1
{
using namespace strx;
using namespace map_info;
using namespace boost::adaptors;

SampleGame::SampleGame()
{
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();
	
	// initialize map and players
	Kernel::LoadMap("small");
	
	auto inu = new SamplePlayerSlot("Inu", PlayerType::HUMAN, 0, "az");
	playerSlots.emplace(inu->GetName(), inu);
	
	auto saru = new SamplePlayerSlot("Saru", PlayerType::AI, 1, "az");
	playerSlots.emplace(saru->GetName(), saru);
	
	for (auto&& playerSlot : playerSlots | map_values)
	{
		Kernel::AddPlayer(playerSlot.get());
	}
}

SampleGame::~SampleGame() = default;

void SampleGame::Start()
{
	gameWidget.reset(new GameWidget());
	gameWidget->SetMap(&Kernel::GetHumanPlayer().GetMap());
	
	gameWidget->showMaximized();
}

}
