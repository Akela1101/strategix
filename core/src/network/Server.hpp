#pragma once

#include <nya/invoker.hpp>

#include "../../strx/NetworkCommon.hpp"
#include "../../strx/strx_fwd.hpp"


namespace strx
{
class Server : public nya::static_invoker<Server, boost::asio::io_context>
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
}  // namespace strx
