#include <boost/asio.hpp>
#include <strx/game/GameSlot.h>
#include <strx/kernel/Message.h>

#include "Connection.h"
#include "Client.h"


namespace strx
{
static GameSlot* game = nullptr;              // current game
static u_p<thread> clientThread;              // client thread
static u_p<tcp::socket> socket;               // client socket
static u_p<Connection> connection;            // single client connection

void Client::StartSession(GameSlot* game)
{
	strx::game = game;
	socket.reset(new tcp::socket(eventLoop));
	auto iEndpoint = tcp::resolver(eventLoop).resolve({ "localhost", "10101" });

	asio::async_connect(*socket, iEndpoint, [](const boost::system::error_code& ec, const tcp::endpoint&)
	{
		if (!ec)
		{
			connection.reset(new Connection(0, move(*socket), ReceiveMessage));
			socket.reset();

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
	invoke([]
	{
		SendMessageOne(make_s<EmptyMessage>(Message::Type::EXIT));
		connection.reset();
	});

	if (clientThread) clientThread->join();
	game = nullptr;
}

void Client::SendMessageOne(s_p<Message> message)
{
	if (connection) connection->Write(message);
}

void Client::ReceiveMessage(s_p<Message> message, PlayerId id)
{
	ignore = id; // == 0
	game->MessageReceived(message);
}
}
