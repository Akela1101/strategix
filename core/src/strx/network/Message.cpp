#include <boost/endian/arithmetic.hpp>

#include "Message.h"


namespace strx
{
s_p<Message> Message::ParseMessage(const char* buffer, size_t len)
{
	switch(auto type = (Type)boost::endian::little_to_native(*(int*)buffer))
	{
		case Type::RQ_CONTEXT: return make_s<Message>(type);
		default: nya_throw << "No message type: " << (int)type;
	}
}

size_t Message::SerializeMessage(char* buffer)
{
	*(int*)buffer = type;
	return sizeof(int);
}

}