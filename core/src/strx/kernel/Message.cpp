#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>

#include "Message.h"
#include "Serialization.h"


namespace strx
{
s_p<Message> Message::Parse(const string& buffer)
{
	using namespace boost::iostreams;
	basic_array_source<char> device(buffer.data(), buffer.size());
	stream is(device);
	boost::archive::binary_iarchive ia(is, boost::archive::no_header);

	s_p<Message> message;
	ia >> message;
	return message;
}

void Message::Serialize(s_p<Message> message, string& buffer)
{
	using namespace boost::iostreams;
	back_insert_device device(buffer);
	stream os(device);
	boost::archive::binary_oarchive oa(os, boost::archive::no_header);
	oa << message;
}

}  // namespace strx
