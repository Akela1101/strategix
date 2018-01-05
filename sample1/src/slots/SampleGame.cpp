#include <graphics/SampleGameWidget.h>
#include <graphics/SampleMapWidget.h>
#include <slots/SampleEntity.h>
#include <slots/SamplePlayer.h>
#include <Strategix.h>
#include <GameWidget.h>
#include <MapInfo.h>

#include "SampleGame.h"


namespace sample1
{
void SampleGame::Configure()
{
	using namespace map_info;
	MapInfo::QRegisterTypes();
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();
}

SampleGame::SampleGame() {}

SampleGame::~SampleGame() = default;

void SampleGame::StartGame(s_p<Map> map)
{
	gameWidget.reset(new SampleGameWidget(GetResourceInfos()));
	mapWidget = gameWidget->CreateMapWidget<SampleMapWidget>();
	mapWidget->SetMap(move(map));

	GameSlot::StartGame(nullptr);//@#~

	gameWidget->showMaximized();
}

u_p<PlayerSlot> SampleGame::AddPlayer(s_p<PlayerMessage> playerMessage)
{
	auto player = make_u<SamplePlayer>(move(playerMessage));

	if (player->GetType() == PlayerType::HUMAN)
	{
		mapWidget->Init(this, player.get());
		connect(player.get(), SamplePlayer::DoResourcesChanged
		        , gameWidget.get(), SampleGameWidget::OnResourcesChanged);
	}
	return player;
}

u_p<EntitySlot> SampleGame::AddEntity(s_p<EntityMessage> entityMessage)
{
	auto entity = make_u<SampleEntity>(move(entityMessage));
	connect(entity.get(), &SampleEntity::DoMoved, mapWidget, &SampleMapWidget::OnEntityMoved);
	connect(entity.get(), &SampleEntity::DoMapMoved, mapWidget, &SampleMapWidget::OnEntityMapMoved);
	return entity;
}

void SampleGame::MineRemoved(IdType id)
{
	qInvoke(mapWidget, [=]() { mapWidget->OnMineRemoved(id); });
}

}
