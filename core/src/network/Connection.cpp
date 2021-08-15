#include <boost/endian/conversion.hpp>
#include <istream>

#include "../../strx/Message.hpp"

#include "Connection.hpp"


namespace strx
{
namespace
{
atomic<ConnectionId> lastConnectionId{0};
}

Connection::Connection(tcp::socket socket, ReceiveCallback receiveCallback, ClosedCallback closedCallback)
        : id(++lastConnectionId)
        , socket(move(socket))
        , receiveCallback(move(receiveCallback))
        , closedCallback(move(closedCallback))
{
	readBuffer.reserve(recommendedMessageLimit);
	writeBuffer.reserve(recommendedMessageLimit);
	Read();
}

Connection::~Connection()
{
	socket.cancel();
	unique_lock lock(readMutex);
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
		error_log << "socket write error: %d (%s)"s % ec.value() % ec.message();
		return;
	}
	asio::write(socket, asio::buffer(writeBuffer.data(), writeBuffer.size()), ec);
	if (ec)
	{
		error_log << "socket write error: %d (%s)"s % ec.value() % ec.message();
		return;
	}
}

void Connection::Read()
{
	readMutex.lock();
	asio::async_read(socket, asio::buffer((char*) &expectedSize, sizeof(int)),
	        [this](boost::system::error_code ec, size_t) {
		        bool result = LockedRead(ec);

		        readMutex.unlock();
		        if (!result) return;

		        Read();
	        });
}

bool Connection::LockedRead(boost::system::error_code ec) noexcept
try
{
	if (OneRead(ec)) return true;

	if (closedCallback) closedCallback(id);
	return false;
}
catch (...)
{
	return false;
}

bool Connection::OneRead(boost::system::error_code ec)
{
	if (ec)
	{
		if (ec != asio::error::eof && ec != asio::error::operation_aborted)
		{
			error_log << "socket read error: %d (%s)"s % ec.value() % ec.message();
		}
		return false;
	}
	boost::endian::little_to_native_inplace(expectedSize);
	readBuffer.resize(expectedSize);
	size_t messageSize = asio::read(socket, asio::buffer(readBuffer.data(), expectedSize));
	if (messageSize != expectedSize)
	{
		error_log << "unable to read the whole buffer";
		return false;
	}

	try
	{
		auto&& message = Message::Parse(readBuffer);
		if (auto&& exitMessage = dp_cast<EmptyMessage>(message);
		        exitMessage && exitMessage->type == Message::Type::EXIT)
		{
			return false;
		}
		receiveCallback(move(message), id);
	}
	catch (exception& e)
	{
		error_log << "Parse message error: " << e.what() << ", size: " << readBuffer.size();
		return false;
	}
	return true;
}

}  // namespace strx
