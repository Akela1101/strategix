#include <boost/endian/arithmetic.hpp>

#include "Message.h"
#include "Connection.h"


namespace strx
{
namespace asio = boost::asio;

Connection::Connection(tcp::socket&& socket) : socket(move(socket))
{
	Read();
}

void Connection::Write(s_p<Message> message)
{
	size_t messageSize = message->SerializeMessage(buffer + sizeof(int));
	*(int*)buffer = boost::endian::native_to_little((int)messageSize);
	
	asio::async_write(socket, asio::buffer(buffer, messageSize + sizeof(int))
			, [this](boost::system::error_code ec, std::size_t)
			{
				if (ec)
				{
					error_log << "socket write error: " << ec.message();
					socket.close();
					return;
				}
			});
}

void Connection::Read()
{
	asio::async_read(socket, asio::buffer((char*)&expectedSize, sizeof(int))
			, [this](boost::system::error_code ec, size_t)
			{
				if (ec)
				{
					error_log << "socket read error: " << ec.message();
					socket.close();
					return;
				}
				boost::endian::little_to_native(expectedSize);
				size_t messageSize = asio::read(socket, asio::buffer(buffer, expectedSize));
				if (messageSize != expectedSize)
				{
					error_log << "unable to read the whole buffer: "
					          << (messageSize < 100 ? buffer : string(buffer, buffer + 100));
					socket.close();
					return;
				}
				
				try { DoMessageReceived(Message::ParseMessage(buffer, messageSize)); }
				catch (exception& e) { error_log << "Unable to parse message: " << e.what(); }
				
				Read();
			});
}

}

