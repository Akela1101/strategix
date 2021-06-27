#pragma once

#include <Strategix_fwd.h>
#include <nya/signal.hpp>
#include "NetworkCommon.h"


namespace strx
{
class Server : public nya::event_loop_holder<boost::asio::io_context>
{
	friend class Kernel;

public:
	Server() = delete;

	static void Run(ushort port);
	static void Finish();

private:
	static void AcceptConnection();
	static void ReceiveMessage(s_p<Message> message, ConnectionId id);
	static void SendMessageOne(s_p<Message> message, ConnectionId id);
	static void SendMessageAll(s_p<Message> message);
	static void ConnectionClosed(ConnectionId id);
};
}
