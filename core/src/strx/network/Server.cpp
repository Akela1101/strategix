#include <boost/asio.hpp>
#include <boost/range/adaptors.hpp>
#include <strx/kernel/Kernel.h>
#include <strx/kernel/Message.h>

#include "Connection.h"
#include "Server.h"


namespace strx
{
static u_p<thread> serverThread;                     // server thread
static u_p<tcp::socket> socket;                      // socket for the next connection
static u_p<tcp::acceptor> acceptor;                  // connection listener
static umap<PlayerId, u_p<Connection>> connections;  // connections


void Server::Run(ushort port)
{
	acceptor.reset(new tcp::acceptor(eventLoop, tcp::endpoint(tcp::v4(), port)));
	socket.reset(new tcp::socket(eventLoop));
	AcceptConnection();

	serverThread.reset(new thread([]()
	{
		nya_thread_name("_serv_");
		trace_log << "Starting server";

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
				error_log << "Unexpected error in server: " << e.what();
			}
		}
	}));
}

void Server::Finish()
{
	if (serverThread) serverThread->join();
}

void Server::AcceptConnection()
{
	acceptor->async_accept(*socket, [](boost::system::error_code ec)
	{
		if (!ec)
		{
			PlayerId id = Kernel::GetNextPlayerId();
			auto connection = new Connection(id, move(*socket), ReceiveMessage);

			connections.emplace(id, connection);
		}
		AcceptConnection();
	});
}

void Server::ReceiveMessage(s_p<Message> message, PlayerId id)
{
	if (!message)
	{
		connections.erase(id);
		return;
	}
	Kernel::invoke(Kernel::OnReceiveMessage, move(message), id);
}

void Server::SendMessageOne(s_p<Message> message, PlayerId id)
{
	auto i = connections.find(id);
	if (i == connections.end())
	{
		error_log << "Player with id %d is not connected!"s % id;
		return;
	}
	i->second->Write(message);
}

void Server::SendMessageAll(s_p<Message> message)
{
	for (const auto& connection : connections | nya::map_values)
	{
		connection->Write(message);
	}
}

}
