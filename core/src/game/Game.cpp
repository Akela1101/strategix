#include "../../strx/Entity.hpp"
#include "../../strx/Message.hpp"
#include "../../strx/Player.hpp"
#include "../network/Client.hpp"

#include "../../strx/Game.hpp"


namespace strx
{
Game::~Game() = default;

void Game::SendMessageOne(s_p<Message> message)
{
	if (!message) nya_throw << "Writting null message.";

	Client::invoke(Client::SendMessageOne, move(message));
}

void Game::ReceiveMessage(s_p<Message> message)
{
	Message::Type type = message->GetType();
	switch (type)
	{
		case Message::Type::PLAYER:
		{
			auto&& playerMessage = sp_cast<PlayerMessage>(message);
			int spot = playerMessage->spot;
			trace_log << "player added: " << spot << (playerMessage->type == PlayerType::SELF ? "*" : "");
			registeredPlayers.emplace(spot, move(playerMessage));
			break;
		}
		case Message::Type::MAP:
		{
			trace_log << "map received";
			OnMapReceived(sp_cast<MapMessage>(message)->map);
			break;
		}
		case Message::Type::START:
		{
			trace_log << "game started";
			OnGameStarted();
			break;
		}
		case Message::Type::ENTITY:
		{
			auto&& entityMessage = sp_cast<EntityMessage>(message);
			trace_log << "entity added: " << entityMessage->id;
			auto&& entity = OnEntityAdded(move(entityMessage));
			entities.emplace(entity->GetId(), move(entity));
			break;
		}
		case Message::Type::RESOURCES:
		{
			const auto& resourcesMessage = sp_cast<ResourcesMessage>(message);
			trace_log << "resources updated";
			OnResourcesChanged(resourcesMessage->resources);
			break;
		}
		case Message::Type::MINE_AMOUNT:
		{
			const auto& mineAmountMessage = sp_cast<MineAmountMessage>(message);
			trace_log << "mine info updated: " << mineAmountMessage->id << " = " << mineAmountMessage->amount;
			OnMineAmountChanged(mineAmountMessage->id, mineAmountMessage->amount);
			break;
		}
		case Message::Type::OBJECT_REMOVED:
		{
			const auto& removalMessage = sp_cast<ObjectRemovedMessage>(message);
			trace_log << "object removed: " << removalMessage->id;
			OnObjectRemoved(removalMessage->id);
			break;
		}
		case Message::Type::MOVE:
		{
			const auto& moveMessage = sp_cast<MapMoveMessage>(message);
			trace_log << "entity move started: " << moveMessage->id;
			entities[moveMessage->id]->MapMoved(moveMessage->from, moveMessage->to);
			break;
		}
		case Message::Type::REAL_MOVE:
		{
			const auto& moveMessage = sp_cast<RealMoveMessage>(message);
			trace_log << "entity move finished: " << moveMessage->id;
			entities[moveMessage->id]->Moved(moveMessage->coord);
			break;
		}
		case Message::Type::HP:
		{
			const auto& hpMessage = sp_cast<HpMessage>(message);
			trace_log << "entity hp: " << hpMessage->id << " = " << hpMessage->hp;
			entities[hpMessage->id]->HpChanged(hpMessage->hp);
			break;
		}
		default: error_log << "Unable to handle message: " << message->GetType().c_str();
	}
}

void Game::OnMapReceived(s_p<Map> map)
{
	for (auto&& playerMessage : registeredPlayers | nya::map_values)
	{
		auto&& player = OnPlayerAdded(move(playerMessage));
		players.emplace(player->GetSpot(), move(player));
	}
	registeredPlayers.clear();
}

}  // namespace strx
