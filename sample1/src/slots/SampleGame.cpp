#include <GameWidget.h>
#include <MapInfo.h>
#include <Strategix.h>
#include <graphics/SampleGameWidget.h>
#include <graphics/SampleMapWidget.h>
#include <slots/SampleEntity.h>
#include <slots/SamplePlayer.h>

#include "SampleGame.h"


namespace sample1
{
SampleGame::SampleGame(int playerSpot) : gameWidget(nullptr), mapWidget(nullptr), playerSpot(playerSpot) {}

SampleGame::~SampleGame() = default;

void SampleGame::Configure()
{
	using namespace map_info;
	MapInfo::QRegisterTypes();
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();
}

void SampleGame::MessageReceived(s_p<Message> message)
{
	qInvoke(this, [this, message] {
		Message::Type type = message->GetType();
		try
		{
			ReceiveMessage(move(message));
		}
		catch (exception& e)
		{
			error_log << "Error while handling message %s: %s"s % type.c_str() % e.what();
		}
	});
}

void SampleGame::GameUpdated(GameId gameId, const GameMessage* gameMessage)
{
	// @#~ start first available game
	if (gameMessage)
	{
		SendMessageOne(make_s<PlayerMessage>(gameId, PlayerType::HUMAN));

		// @#~ start right away
		SendMessageOne(make_s<EmptyMessage>(Message::Type::START));
	}
}

void SampleGame::StartGame(s_p<Map> map)
{
	gameWidget.reset(new SampleGameWidget(GetResourceInfos()));
	mapWidget = gameWidget->CreateMapWidget<SampleMapWidget>();
	mapWidget->SetMap(move(map));

	GameSlot::StartGame(nullptr);  //@#~

	gameWidget->show();
}

u_p<PlayerSlot> SampleGame::AddPlayer(s_p<PlayerMessage> playerMessage)
{
	auto player = make_u<SamplePlayer>(move(playerMessage));

	if (player->GetType() == PlayerType::HUMAN) { mapWidget->Init(this, player.get()); }
	return player;
}

u_p<EntitySlot> SampleGame::AddEntity(s_p<EntityMessage> entityMessage)
{
	auto entity = make_u<SampleEntity>(move(entityMessage), mapWidget);
	auto mapEntity = (MapEntity*) mapWidget->GetMapObject(entity->GetId());
	mapEntity->SetMaxHp(entity->GetMaxHp());
	return entity;
}

void SampleGame::ResourcesChanged(const Resources& newResources)
{
	gameWidget->OnResourcesChanged(newResources);
}

void SampleGame::ObjectRemoved(IdType id)
{
	mapWidget->ObjectRemoved(id);
}

}  // namespace sample1
