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
using namespace map_info;
using namespace boost::adaptors;

void SampleGame::Configure()
{
	MapInfo::QRegisterTypes();
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();
}

SampleGame::SampleGame() {}

SampleGame::~SampleGame() = default;

void SampleGame::HandleMessageImpl(s_p<Message> message)
{
	switch (message->GetType())
	{
	case Message::Type::VECTOR:
	{
		for (auto& element : *sp_cast<MessageVector>(message))
		{
			HandleMessageImpl(move(element));
		}
		break;
	}
	case Message::Type::CONTEXT:
	{
		resourceInfos = sp_cast<ContextMessage>(message)->resourceInfos;
		break;
	}
	case Message::Type::GAME:
	{
		// @#~ joint first game here
		auto&& gameMessage = sp_cast<GameMessage>(message);
		SendMessageOne(make_s<PlayerMessage>(gameMessage->id, 1, PlayerType::HUMAN, "Inu", "az"));
		SendMessageOne(make_s<PlayerMessage>(gameMessage->id, 3, PlayerType::AI, "Saru", "az"));

		// @#~ start right away
		SendMessageOne(make_s<EmptyMessage>(Message::Type::START));
		break;
	}
	case Message::Type::PLAYER:
	{
		auto&& playerMessage = sp_cast<PlayerMessage>(message);
		int id = playerMessage->id;
		registeredPlayers.emplace(id, move(playerMessage));
		break;
	}
	case Message::Type::MAP:
	{
		StartGame(*sp_cast<MapMessage>(message));
		break;
	}
	case Message::Type::ENTITY:
	{
		auto&& entityMessage = sp_cast<EntityMessage>(message);
		int playerId = entityMessage->playerId;
		players[playerId]->EntityAdded(move(entityMessage));
		break;
	}
	default:
		error_log << "Unable to handle message: " << message->GetType().c_str();
	}
}

void SampleGame::StartGame(MapMessage& mapMessage)
{
	gameWidget.reset(new SampleGameWidget(resourceInfos));
	mapWidget = gameWidget->CreateMapWidget<SampleMapWidget>();
	mapWidget->SetMap(mapMessage.map);

	for (auto&& playerMessage : registeredPlayers | nya::map_values)
	{
		AddPlayer(move(playerMessage));
	}
	registeredPlayers.clear();

	gameWidget->showMaximized();
}

void SampleGame::AddPlayer(s_p<PlayerMessage> playerMessage)
{
	auto player = make_u<SamplePlayer>(move(playerMessage));

	mapWidget->AddPlayer(player.get());
	if (player->GetType() == PlayerType::HUMAN)
	{
		InitHuman(player.get());
	}

	players.emplace(player->GetId(), move(player));
}

void SampleGame::InitHuman(SamplePlayer* player)
{
	QObject::connect(player, SamplePlayer::DoResourcesChanged
	        , gameWidget.get(), SampleGameWidget::OnResourcesChanged);
}

void SampleGame::HandleMessage(s_p<Message> message)
{
	HandleMessageImpl(move(message));
}

}
