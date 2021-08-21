#include <boost/asio.hpp>
#include <memory>
#include <utility>

#include "../../strx/Message.hpp"
#include "../../strx/User.hpp"

#include "Client.hpp"
#include "Connection.hpp"


namespace strx
{
static User* user = nullptr;        // current user
static u_p<thread> clientThread;    // client thread
static u_p<tcp::socket> socket;     // client socket
static u_p<Connection> connection;  // single client connection

void Client::StartSession(User* user)
{
	strx::user = user;
	socket = std::make_unique<tcp::socket>(eventLoop);
	auto iEndpoint = tcp::resolver(eventLoop).resolve({"localhost", "10101"});

	asio::async_connect(*socket, iEndpoint, [](const boost::system::error_code& ec, const tcp::endpoint&) {
		if (!ec)
		{
			connection = std::make_unique<Connection>(move(*socket), ReceiveMessage);
			socket.reset();

			connection->Write(make_s<EmptyMessage>(Message::Type::GET_CONTEXT));
		}
	});

	clientThread = std::make_unique<thread>([]() {
		nya_thread_name("_clnt_");
		trace_log << "Starting client";

		bool running = true;
		while (running)
		{
			try
			{
				eventLoop.run();
				running = false;
			}
			catch (exception& e)
			{
				error_log << "Unexpected error in client: " << e.what();
			}
		}
	});
}

void Client::StopSession()
{
	SendMessageOne(make_s<EmptyMessage>(Message::Type::EXIT));
	connection.reset();

	if (clientThread) clientThread->join();
	user = nullptr;
}

void Client::SendMessageOne(s_p<Message> message)
{
	if (connection) connection->Write(move(message));
}

void Client::ReceiveMessage(s_p<Message> message, PlayerId)
{
	user->MessageReceived(move(message));
}
}  // namespace strx
