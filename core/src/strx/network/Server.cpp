#include <boost/asio.hpp>
#include <boost/range/adaptors.hpp>
#include <strx/kernel/Kernel.h>
#include <strx/network/Message.h>

#include "Connection.h"
#include "Server.h"


namespace strx
{
static u_p<thread> serverThread;              // server thread
u_p<tcp::socket> socket;                      // socket for the next connection
u_p<tcp::acceptor> acceptor;                  // connection listener
umap<NetId, u_p<Connection>> connections;     // connections


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

void Server::SendMessageImpl(std::shared_ptr<Message> message, NetId clientId)
{
	connections[clientId]->Write(message);
}

void Server::SendMessageAllImpl(s_p<Message> message)
{
	for (const auto& connection : connections | nya::map_values)
	{
		connection->Write(message);
	}
}

void Server::AcceptConnection()
{
	acceptor->async_accept(*socket, [](boost::system::error_code ec)
	{
		if (!ec)
		{
			NetId id = to_netid(socket->remote_endpoint());
			auto connection = new Connection(move(*socket), ReceiveMessage);

			connections.emplace(id, connection);
		}
		AcceptConnection();
	});
}

void Server::ReceiveMessage(s_p<Message> message, NetId id)
{
	Kernel::invoke(Kernel::OnReceiveMessage, message, id);
}
}
