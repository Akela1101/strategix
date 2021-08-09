#pragma once

#include <nya/invoker.hpp>

#include "../../strx/NetworkCommon.hpp"
#include "../../strx/strx_fwd.hpp"


namespace strx
{
class Client : public nya::static_invoker<Client, boost::asio::io_context>
{
	friend class User;
	Client() = delete;

public:
	static void StartSession(User* user);
	static void StopSession();

	static void SendMessageOne(s_p<Message> message);
	static void ReceiveMessage(s_p<Message> message, PlayerId id);
};
}  // namespace strx
