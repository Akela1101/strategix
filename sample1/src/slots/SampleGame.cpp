#include <graphics/SampleGameWidget.h>
#include <graphics/SampleMapWidget.h>
#include <strx/player/Player.h>
#include <slots/SampleEntitySlot.h>
#include <slots/SamplePlayerSlot.h>
#include <Strategix.h>
#include <GameWidget.h>
#include <MapInfo.h>

#include "SampleGame.h"


namespace sample1
{
using namespace map_info;
using namespace boost::adaptors;

void SampleGame::Configure()
{
	MapInfo::QRegisterTypes();
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();
}

SampleGame::SampleGame()
		: gameWidget(new SampleGameWidget())
		, mapWidget(gameWidget->CreateMapWidget<SampleMapWidget>())
{
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
	if (player->GetType() == PlayerType::HUMAN)
	{
		InitHuman(playerSlot);
	}
	
	// available resources
	player->AddResource(Resource("gold", 1000));
}

void SampleGame::InitHuman(SamplePlayerSlot* playerSlot)
{
	QObject::connect(playerSlot, SamplePlayerSlot::DoResourcesChanged
			, gameWidget.get(), SampleGameWidget::OnResourcesChanged);
}

}
