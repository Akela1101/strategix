#include <MapInfo.hpp>
#include <strx/strx.hpp>

#include "SampleGame.hpp"
#include "SampleUser.hpp"


namespace sample1
{
void SampleUser::Configure()
{
	using namespace map_info;
	MapInfo::QRegisterTypes();
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();
}

SampleUser::~SampleUser() = default;

void SampleUser::MessageReceived(s_p<Message> message)
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

void SampleUser::HandleContext()
{
	//todo: add game from gui
	if (userId == 1)
	{
		auto gameMessage = make_s<GameMessage>();
		gameMessage->mapName = "small";
		gameMessage->creatorName = "user 1";
		SendMessageOne(move(gameMessage));
	}
}

void SampleUser::GameUpdated(GameId gameId, const GameMessage* gameMessage)
{
	//
}

u_p<Game> SampleUser::AddGame(GameId gameId, ResourceInfosType resourceInfos)
{
	SendMessageOne(make_s<PlayerMessage>(gameId, PlayerType::HUMAN));
	SendMessageOne(make_s<EmptyMessage>(Message::Type::START));

	return make_u<SampleGame>(userId, move(resourceInfos));
}

}  // namespace sample1
