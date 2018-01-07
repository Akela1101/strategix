#include <strx/entity/EntitySlot.h>
#include <strx/kernel/Message.h>
#include <strx/network/Client.h>
#include <strx/player/PlayerSlot.h>

#include "GameSlot.h"


namespace strx
{
GameSlot::GameSlot()
{
	Client::StartSession(this);
}

GameSlot::~GameSlot()
{
	Client::StopSession();
}

EntitySlot&GameSlot::GetEntitySlot(IdType id)
{
	return *entities[id];
}

void GameSlot::SendMessageOne(s_p<Message> message)
{
	if (!message) nya_throw << "Writting null message.";

	Client::invoke(Client::SendMessageOne, move(message));
}

void GameSlot::ReceiveMessage(s_p<Message> message)
{
	switch (message->GetType())
	{
	case Message::Type::VECTOR:
	{
		for (auto& element : *sp_cast<MessageVector>(message))
		{
			ReceiveMessage(move(element));
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
		// @#~ join first game here
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
		int spot = playerMessage->spot;
		registeredPlayers.emplace(spot, move(playerMessage));
		break;
	}
	case Message::Type::MAP:
	{
		StartGame(sp_cast<MapMessage>(message)->map);
		break;
	}
	case Message::Type::ENTITY:
	{
		auto&& entityMessage = sp_cast<EntityMessage>(message);
		auto&& entity = AddEntity(move(entityMessage));
		entities.emplace(entity->GetId(), move(entity));
		break;
	}
	case Message::Type::RESOURCES:
	{
		const auto& resourcesMessage = sp_cast<ResourcesMessage>(message);
		ResourcesChanged(resourcesMessage->resources);
		break;
	}
	case Message::Type::MINE_AMOUNT:
	{
		const auto& mineAmountMessage = sp_cast<MineAmountMessage>(message);
		MineAmountChanged(mineAmountMessage->id, mineAmountMessage->amount);
		break;
	}
	case Message::Type::OBJECT_REMOVED:
	{
		const auto& removalMessage = sp_cast<ObjectRemovedMessage>(message);
		ObjectRemoved(removalMessage->id);
		break;
	}
	case Message::Type::MOVE:
	{
		const auto& moveMessage = sp_cast<MapMoveMessage>(message);
		entities[moveMessage->id]->MapMoved(moveMessage->from, moveMessage->to);
		break;
	}
	case Message::Type::REAL_MOVE:
	{
		const auto& moveMessage = sp_cast<RealMoveMessage>(message);
		entities[moveMessage->id]->Moved(moveMessage->coord);
		break;
	}
	default:
		error_log << "Unable to handle message: " << message->GetType().c_str();
	}
}

void GameSlot::StartGame(s_p<Map> map)
{
	for (auto&& playerMessage : registeredPlayers | nya::map_values)
	{
		auto&& player = AddPlayer(move(playerMessage));
		players.emplace(player->GetSpot(), move(player));
	}
	registeredPlayers.clear();
}

}
