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
}

SampleGame::~SampleGame() = default;

void SampleGame::Start()
{
	Kernel::LoadMap("small");
	Kernel::AddPlayer("Inu", PlayerType::HUMAN, 1, "az");
	Kernel::AddPlayer("Saru", PlayerType::AI, 3, "az");
}

void SampleGame::PlayerAdded(Player* player)
{
	auto playerSlot = new SamplePlayerSlot(player);
	playerSlots.emplace(player->GetName(), playerSlot);
	
	if (player->GetType() == PlayerType::HUMAN)
	{
		gameWidget.reset(new GameWidget());
		gameWidget->SetMap(&player->GetMap());
		gameWidget->showMaximized();
	}
}

}
