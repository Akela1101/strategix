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

void GameSlot::SendOneMessage(s_p<Message> message)
{
	Client::invoke(Client::SendMessage, move(message));
}
}
