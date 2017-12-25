#pragma once

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include "Message.h"


#define StrxSerialization(M)             \
BOOST_CLASS_EXPORT(M)                    \
BOOST_CLASS_IMPLEMENTATION(M, boost::serialization::object_serializable) \
namespace boost {                        \
namespace serialization {                \
template<class Archive>                  \
void serialize(Archive& ar, M& m, uint)

StrxSerialization(strx::Message::Type)
{
	ar & (strx::Message::Type::value_type&)m;
}}}

StrxSerialization(strx::Message)
{
	ar & m.type;
}}}

StrxSerialization(strx::ContextMessage)
{
	ar & base_object<strx::Message>(m);
	ar & m.resourceInfos;
}}}
