#include <graphics/SampleGameWidget.h>
#include <graphics/SampleMapWidget.h>
#include <strx/player/Player.h>
#include <slots/SampleEntiSlot.h>
#include <slots/SamplePlayerSlot.h>
#include <Strategix.h>
#include <GameWidget.h>
#include <MapInfo.h>

#include "SampleGame.h"


namespace sample1
{
using namespace strx;
using namespace map_info;
using namespace boost::adaptors;

SampleGame::SampleGame()
		: gameWidget(new SampleGameWidget())
		, mapWidget(gameWidget->CreateMapWidget<SampleMapWidget>())
{
	// @#~ static call
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();
}

SampleGame::~SampleGame() = default;

void SampleGame::Start()
{
	Kernel::LoadMap("small");
	Kernel::AddPlayer("Inu", PlayerType::HUMAN, 1, "az");
	Kernel::AddPlayer("Saru", PlayerType::AI, 3, "az");
	
	gameWidget->showMaximized();
}

void SampleGame::PlayerAdded(Player* player)
{
	auto playerSlot = new SamplePlayerSlot(player);
	playerSlots.emplace(player->GetName(), playerSlot);
	
	mapWidget->AddPlayer(playerSlot);
}

}
