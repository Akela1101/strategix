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

void SampleGame::Started()
{

}

void SampleGame::HandleMessageInstance(s_p<Message> message)
{
	switch (message->GetType())
	{
	case Message::Type::VECTOR:
	{
		for (auto& element : *sp_cast<MessageVector>(message))
		{
			HandleMessageInstance(move(element));
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
		SendOneMessage(make_s<PlayerMessage>(gameMessage->id, 1, PlayerType::HUMAN, "Inu", "az"));
		SendOneMessage(make_s<PlayerMessage>(gameMessage->id, 3, PlayerType::AI, "Saru", "az"));

		// @#~ start right away
		SendOneMessage(make_s<EmptyMessage>(Message::Type::START));
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
	default:
		error_log << "Unable to handle message: " << message->GetType().c_str();
	}
}

void SampleGame::StartGame(MapMessage& mapMessage)
{
	gameWidget.reset(new SampleGameWidget(resourceInfos));
	mapWidget = gameWidget->CreateMapWidget<SampleMapWidget>();
	mapWidget->SetMap(mapMessage.map);

	for (auto&& player : registeredPlayers | nya::map_values)
	{
		AddPlayer(move(player));
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

	// available resources
	//TODO: player->AddResource(Resource("gold", 1000));

	playerSlots.emplace(player->GetName(), move(player));
}

void SampleGame::InitHuman(SamplePlayer* player)
{
	QObject::connect(player, SamplePlayer::DoResourcesChanged
	        , gameWidget.get(), SampleGameWidget::OnResourcesChanged);
}

void SampleGame::HandleMessage(s_p<Message> message)
{
	HandleMessageInstance(move(message));
}

}
