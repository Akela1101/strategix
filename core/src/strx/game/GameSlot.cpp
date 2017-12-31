#include <strx/network/Client.h>

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

void GameSlot::SendMessageOne(s_p<Message> message)
{
	Client::invoke(Client::SendMessageOne, move(message));
}
}
