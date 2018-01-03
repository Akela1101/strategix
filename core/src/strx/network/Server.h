#pragma once

#include <Strategix_fwd.h>
#include <nya/signal.hpp>
#include "NetworkCommon.h"


namespace strx
{
class Server : public nya::event_loop_holder<Server>
{
	friend class Kernel;
	Server() = delete;

public:
	static void Run(ushort port);
	static void Finish();

private:
	static void AcceptConnection();
	static void ReceiveMessage(s_p<Message> message, PlayerId id);
	static void SendMessageOne(s_p<Message> message, PlayerId id);
	static void SendMessageAll(s_p<Message> message);
};
}
