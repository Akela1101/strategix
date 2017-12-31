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

	static void SendMessageOne(s_p<Message> message, NetId clientId) { invoke(SendMessageImpl, move(message), clientId); }
	static void SendMessageAll(s_p<Message> message) { invoke(SendMessageAllImpl, move(message)); }

private:
	static void SendMessageImpl(s_p<Message> message, NetId clientId);
	static void SendMessageAllImpl(s_p<Message> message);
	static void AcceptConnection();
	static void ReceiveMessage(s_p<Message> message, NetId id);
};
}
