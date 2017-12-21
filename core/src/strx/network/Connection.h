#pragma once

#include <Strategix_fwd.h>
#include <boost/asio.hpp>
#include <nya/signal.hpp>


namespace strx
{
using boost::asio::ip::tcp;

class Connection : boost::noncopyable
{
	tcp::socket socket;
	char buffer[maxMessageSize];
	int expectedSize;
	
public:
	Connection(tcp::socket&& socket);
	
	void Write(s_p<Message> message);
	
	nya::sig<void(s_p<Message>)> DoMessageReceived;
	
private:
	void Read();
};
}
