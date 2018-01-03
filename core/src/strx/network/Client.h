#pragma once

#include <Strategix_fwd.h>
#include <nya/signal.hpp>
#include "NetworkCommon.h"

namespace strx
{
class Client : public nya::event_loop_holder<Client>
{
	friend class GameSlot;
	Client() = delete;

public:
	static void StartSession(GameSlot* game);
	static void StopSession();

private:
	static void SendMessageOne(s_p<Message> message);
	static void ReceiveMessage(s_p<Message> message, PlayerId id);
};
}
