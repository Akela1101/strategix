#include <boost/asio.hpp>

#include "Connection.h"
#include "Client.h"
#include "Message.h"


namespace strx
{
using boost::asio::ip::tcp;

static u_p<thread> clientThread;              // client thread
static u_p<tcp::socket> socket;               // client socket
static u_p<tcp::resolver> resolver;           // ip resolver
static u_p<Connection> connection;            // single client connection

void Client::StartSession()
{
	socket.reset(new tcp::socket(eventLoop));
	resolver.reset(new tcp::resolver(eventLoop));
	auto iEndpoint = resolver->resolve({ "localhost", "10101" });
	
	boost::asio::async_connect(*socket, iEndpoint, [](boost::system::error_code ec , tcp::resolver::iterator)
	{
		if (!ec)
		{
			connection.reset(new Connection(move(*socket)));
			
			connection->Write(make_s<Message>(Message::Type::RQ_CONTEXT));
		}
	});
	
	clientThread.reset(new thread([]()
	{
		nya::SetThreadName("_clnt_");
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
	if (clientThread) clientThread->join();
}
}
