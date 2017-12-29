#pragma once

#include <Strategix_fwd.h>
#include <nya/signal.hpp>
#include "NetworkCommon.h"


namespace strx
{
class Server : public nya::event_loop_holder<Server>
{
	Server() = delete;

public:
	static void Run(ushort port);
	static void Finish();

	static void OnSendMessage(s_p<Message> message, NetId clientId);
	static void OnSendMessageAll(s_p<Message> message);

private:
	static void AcceptConnection();
	static void ReceiveMessage(s_p<Message> message, NetId id);
};
}
