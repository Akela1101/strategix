#include <boost/asio.hpp>
#include <strx/game/GameSlot.h>

#include "Connection.h"
#include "Client.h"
#include "Message.h"


namespace strx
{
static GameSlot* game = nullptr;              // current game
static u_p<thread> clientThread;              // client thread
static u_p<tcp::socket> socket;               // client socket
static u_p<tcp::resolver> resolver;           // ip resolver
static u_p<Connection> connection;            // single client connection

void Client::StartSession(GameSlot* game)
{
	strx::game = game;
	socket.reset(new tcp::socket(eventLoop));
	resolver.reset(new tcp::resolver(eventLoop));
	auto iEndpoint = resolver->resolve({ "localhost", "10101" });

	boost::asio::async_connect(*socket, iEndpoint, [](const boost::system::error_code& ec, const tcp::endpoint&)
	{
		if (!ec)
		{
			connection.reset(new Connection(move(*socket), ReceiveMessage));

			connection->Write(make_s<EmptyMessage>(Message::Type::CONTEXT));
		}
	});

	clientThread.reset(new thread([]()
	{
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
	}));
}

void Client::StopSession()
{
	game = nullptr;
	if (clientThread) clientThread->join();
}

void Client::SendMessage(s_p<Message> message)
{
	connection->Write(message);
}

void Client::ReceiveMessage(s_p<Message> message, NetId id)
{
	ignore = id;
	if (game) game->OnReceiveMessage(message);
}
}
