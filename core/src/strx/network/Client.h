#pragma once

#include <Strategix_fwd.h>
#include <nya/signal.hpp>
#include "NetworkCommon.h"

namespace strx
{
class Client : public nya::event_loop_holder<Client>
{
	Client() = delete;

public:
	static void StartSession(GameSlot* game);
	static void StopSession();

	static void SendMessageOne(s_p<Message> message);

private:
	static void ReceiveMessage(s_p<Message> message, NetId id);
};
}
