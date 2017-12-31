#include <istream>
#include <sstream>
#include <boost/endian/arithmetic.hpp>
#include <strx/kernel/Message.h>

#include "Connection.h"


namespace strx
{
Connection::Connection(NetId id, tcp::socket&& socket, const function<void(s_p<Message>, NetId)>& ReceiveMessage)
        : id(id)
        , socket(move(socket))
        , ReceiveMessage(ReceiveMessage)
{
	readBuffer.reserve(recommendedMessageLimit);
	writeBuffer.reserve(recommendedMessageLimit);
	Read();
}

void Connection::Write(s_p<Message> message)
{
	writeBuffer.clear();
	Message::Serialize(message, writeBuffer);
	int messageSize = writeBuffer.size();
	if (messageSize > recommendedMessageLimit)
	{
		info_log << "Writting very long message. Try to shrink format of " << message->GetType().c_str();
	}

	boost::endian::native_to_little_inplace(messageSize);
	auto sizeBuffer = asio::buffer(&messageSize, sizeof(int));
	boost::system::error_code ec;

	asio::write(socket, sizeBuffer, ec);
	if (ec)
	{
		error_log << "socket write error: " << ec.message();
		socket.close();
		return;
	}
	asio::write(socket, asio::buffer(writeBuffer.data(), writeBuffer.size()), ec);
	if (ec)
	{
		error_log << "socket write error: " << ec.message();
		socket.close();
		return;
	}
}

void Connection::Read()
{
	asio::async_read(socket, asio::buffer((char*)&expectedSize, sizeof(int))
	        , [this](boost::system::error_code ec, size_t)
	        {
		        if (ec)
				{
					error_log << "socket read error: " << ec.message();
					Close();
					return;
				}
				boost::endian::little_to_native_inplace(expectedSize);
				readBuffer.resize(expectedSize);
				size_t messageSize = asio::read(socket, asio::buffer(readBuffer.data(), expectedSize));
				if (messageSize != expectedSize)
				{
					error_log << "unable to read the whole buffer";
					Close();
					return;
				}

				try { ReceiveMessage(Message::Parse(readBuffer), id); }
				catch (exception& e) { error_log << "Unable to parse message: " << e.what(); }

				Read();
	        });
}

void Connection::Close()
{
	socket.close();
	ReceiveMessage(nullptr, id);
}

}

