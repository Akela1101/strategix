#include <graphics/GameWidget.h>
#include <Strategix.h>
#include <slots/SampleEntiSlot.h>
#include <slots/SamplePlayerSlot.h>

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
	// initialize map and players
	Kernel::LoadMap("1x1");
	
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
	MapInfo::LoadTerrainInfos();
	MapInfo::LoadObjectInfos();
	
	gameWidget.reset(new GameWidget());
	gameWidget->LoadFromFile("maps/small.map");
	PlaceEntis();
	
	gameWidget->showMaximized();
}

void SampleGame::PlaceEntis()
{
	auto inuWorker = new SampleEntiSlot("az_worker");
	auto saruWorker = new SampleEntiSlot("az_worker");
	
	playerSlots["Inu"]->AddEnti(inuWorker);
	playerSlots["Saru"]->AddEnti(saruWorker);
}

}
