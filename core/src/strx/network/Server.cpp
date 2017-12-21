#include <boost/asio.hpp>
#include <strx/kernel/Kernel.h>

#include "Connection.h"
#include "Server.h"


namespace strx
{
using boost::asio::ip::tcp;

static u_p<thread> serverThread;              // server thread
u_p<tcp::socket> socket;                      // socket for the next connection
u_p<tcp::acceptor> acceptor;                  // connection listener
vector<u_p<Connection>> connections;          // connections


void AcceptConnection()
{
	acceptor->async_accept(*socket, [](boost::system::error_code ec)
	{
		if (!ec)
		{
			auto connection = new Connection(move(*socket));
			connections.emplace_back(connection);
			Kernel::Connect(connection->DoMessageReceived, Kernel::OnMessageReceived);
		}
		AcceptConnection();
	});
}

void Server::Run(ushort port)
{
	acceptor.reset(new tcp::acceptor(eventLoop, tcp::endpoint(tcp::v4(), port)));
	socket.reset(new tcp::socket(eventLoop));
	AcceptConnection();
	
	serverThread.reset(new thread([]()
	{
		nya::SetThreadName("_serv_");
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
}