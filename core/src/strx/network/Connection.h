#pragma once

#include <functional>
#include <Strategix_fwd.h>
#include <strx/network/NetworkCommon.h>
#include <boost/asio.hpp>
#include <nya/signal.hpp>


namespace strx
{
class Connection : boost::noncopyable
{
	NetId id;
	tcp::socket socket;
	const function<void(s_p<Message>, NetId)> ReceiveMessage;

	string writeBuffer;
	string readBuffer;
	int expectedSize;

public:
	Connection(NetId id, tcp::socket&& socket, const function<void(s_p<Message>, NetId)>& ReceiveMessage);

	NetId GetId() const { return id; }
	void Write(s_p<Message> message);

private:
	void Read();
	void Close();
};
}
