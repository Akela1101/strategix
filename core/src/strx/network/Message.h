#pragma once

#include <Strategix_fwd.h>
#include <nya/enum.hpp>

namespace strx
{
struct Message : boost::noncopyable
{
#   define MessageTypeEnumDef(K, V) \
		K(RQ_CONTEXT)
	nya_enum(Type, MessageTypeEnumDef)
	
	Type type;
	
	static s_p<Message> ParseMessage(const char* buffer, size_t len);
	
	Message(Type type) : type(type) {}
	
	virtual size_t SerializeMessage(char* buffer);
};
}