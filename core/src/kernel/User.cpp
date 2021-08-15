#include "../../strx/Entity.hpp"
#include "../../strx/Game.hpp"
#include "../../strx/Message.hpp"
#include "../../strx/Player.hpp"
#include "../network/Client.hpp"

#include "../../strx/User.hpp"


namespace strx
{
User::User()
{
	Client::StartSession(this);
}

User::~User()
{
	Client::StopSession();
}

void User::SendMessageOne(s_p<Message> message)
{
	if (!message) nya_throw << "Writting null message.";

	Client::invoke(Client::SendMessageOne, move(message));
}

void User::ReceiveMessage(s_p<Message> message)
{
	Message::Type type = message->GetType();
	switch (type)
	{
		case Message::Type::VECTOR:
		{
			for (auto& element : *sp_cast<MessageVector>(message)) { ReceiveMessage(move(element)); }
			break;
		}
		case Message::Type::CONTEXT:
		{
			trace_log << "context received";
			auto contextMessage = sp_cast<ContextMessage>(message);
			resourcesContext = contextMessage->resourcesContext;
			HandleContext(contextMessage.get());
			break;
		}
		case Message::Type::GAME:
		{
			auto&& gameMessage = sp_cast<GameMessage>(message);
			trace_log << "game received";
			HandleGame(gameMessage.get());
			break;
		}
		default:
		{
			if (game)  //
			{
				game->ReceiveMessage(move(message));
			}
			else
			{
				error_log << "Unable to handle message: " << message->GetType().c_str();
			}
		}
	}
}

void User::JoinGame(GameId gameId)
{
	game = CreateGame(resourcesContext);

	SendMessageOne(make_s<PlayerMessage>(gameId, PlayerType::HUMAN));
}

}  // namespace strx
