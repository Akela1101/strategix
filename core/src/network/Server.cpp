#include <boost/asio.hpp>
#include <boost/range/adaptors.hpp>

#include "../../strx/Kernel.hpp"
#include "../../strx/Message.hpp"

#include "Connection.hpp"
#include "Server.hpp"


namespace strx
{
namespace
{
u_p<thread> serverThread;                         // server thread
u_p<tcp::socket> socket;                          // socket for the next connection
u_p<tcp::acceptor> acceptor;                      // connection listener
umap<ConnectionId, u_p<Connection>> connections;  // connections
}  // namespace


void Server::Run(ushort port)
{
	acceptor.reset(new tcp::acceptor(eventLoop, tcp::endpoint(tcp::v4(), port)));
	socket.reset(new tcp::socket(eventLoop));
	AcceptConnection();

	serverThread.reset(new thread([]() {
		nya_thread_name("_serv_");
		trace_log << "starting server";

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
		trace_log << "stopping server";
	}));
}

void Server::Finish()
{
	if (serverThread) serverThread->join();
}

void Server::AcceptConnection()
{
	acceptor->async_accept(*socket, [](boost::system::error_code ec) {
		if (!ec)
		{
			auto connection = make_u<Connection>(move(*socket), ReceiveMessage, ConnectionClosed);

			connections.emplace(connection->GetId(), move(connection));
		}
		AcceptConnection();
	});
}

void Server::ReceiveMessage(s_p<Message> message, ConnectionId id)
{
	Kernel::invoke(Kernel::OnReceiveMessage, move(message), id);
}

void Server::SendMessageOne(s_p<Message> message, ConnectionId id)
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
	for (const auto& connection : connections | nya::map_values) connection->Write(message);
}

void Server::ConnectionClosed(ConnectionId id)
{
	connections.erase(id);
}

}  // namespace strx
