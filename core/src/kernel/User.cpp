#include "../../strx/EntitySlot.hpp"
#include "../../strx/GameSlot.hpp"
#include "../../strx/Message.hpp"
#include "../../strx/PlayerSlot.hpp"
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
			resourceInfos = sp_cast<ContextMessage>(message)->resourceInfos;
			HandleContext();
			break;
		}
		case Message::Type::GAME:
		{
			auto&& gameMessage = sp_cast<GameMessage>(message);
			trace_log << "game received";
			GameUpdated(gameMessage->id, gameMessage.get());

			//todo: select game - now it starts first available game
			game = AddGame(gameMessage->id, resourceInfos);
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

}  // namespace strx
