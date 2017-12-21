#include <strx/network/Client.h>

#include "GameSlot.h"


namespace strx
{
GameSlot::GameSlot()
{
	Client::StartSession();
}

GameSlot::~GameSlot()
{
	Client::StopSession();
}
}
