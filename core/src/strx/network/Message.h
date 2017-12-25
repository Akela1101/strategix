#pragma once

#include <nya/enum.hpp>
#include <Strategix_fwd.h>
#include "NetworkCommon.h"

namespace strx
{
struct Message : boost::noncopyable
{
#   define MessageTypeEnumDef(K, V) \
		K(RQ_CONTEXT) \
		K(CONTEXT)
	nya_enum(Type, MessageTypeEnumDef)

	Type type;

	Message() = default;
	Message(Type type) : type(type) {}
	virtual ~Message() = default;

	static s_p<Message> Parse(const string& buffer);
	static void Serialize(s_p<Message> message, string& buffer);
};

struct ContextMessage : Message
{
	ResourceInfosType resourceInfos;

	ContextMessage() = default;
	ContextMessage(const ResourceInfosType& resourceInfos) : Message(Type::CONTEXT), resourceInfos(resourceInfos) {}
};
}
