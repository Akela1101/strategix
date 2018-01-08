#pragma once

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>
#include <strx/map/Map.h>
#include "Message.h"


#define StrxSerializationSimple(M)       \
namespace boost {                        \
namespace serialization {                \
template<class Archive>                  \
void serialize(Archive& ar, M& m, uint)

#define StrxSerialization(M)             \
BOOST_CLASS_EXPORT(M)                    \
BOOST_CLASS_IMPLEMENTATION(M, boost::serialization::object_serializable) \
StrxSerializationSimple(M)

#define StrxSerializationSplit(M) \
BOOST_SERIALIZATION_SPLIT_FREE(M) \
BOOST_CLASS_EXPORT(M)             \
BOOST_CLASS_IMPLEMENTATION(M, boost::serialization::object_serializable)


StrxSerializationSimple(strx::MapCoord)
{
	ar & m.x;
	ar & m.y;
}}}

StrxSerializationSimple(strx::RealCoord)
{
	ar & m.x;
	ar & m.y;
}}}

StrxSerializationSimple(strx::Resources)
{
	ar & (strx::ResourcesType&)m;
}}}

StrxSerializationSimple(strx::Message::Type)
{
	ar & (strx::Message::Type::value_type&)m;
}}}

StrxSerialization(strx::Message)
{
}}}

StrxSerialization(strx::MessageVector)
{
	ar & base_object<strx::Message>(m);
	ar & base_object<std::vector<s_p<strx::Message>>>(m);
}}}

StrxSerialization(strx::EmptyMessage)
{
	ar & base_object<strx::Message>(m);
	ar & m.type;
}}}

StrxSerialization(strx::ContextMessage)
{
	ar & base_object<strx::Message>(m);
	ar & m.resourceInfos;
}}}

StrxSerialization(strx::GameMessage)
{
	ar & base_object<strx::Message>(m);
	ar & m.id;
	ar & m.started;
	ar & m.mapName;
	ar & m.creatorName;
}}}

StrxSerialization(strx::PlayerMessage)
{
	ar & base_object<strx::Message>(m);
	ar & m.gameId;
	ar & m.spot;
	ar & m.type;
	ar & m.name;
	ar & m.race;
}}}

StrxSerializationSplit(strx::MapMessage)
namespace boost { namespace serialization {
template<class Archive>
void save(Archive& ar, const strx::MapMessage& m, uint)
{
	ar << base_object<strx::Message>(m);
	ar << m.map->GetName();
	ar << m.map->SaveToString();
}

template<class Archive>
void load(Archive& ar, strx::MapMessage& m, uint)
{
	std::string name, data;
	ar >> base_object<strx::Message>(m);
	ar >> name >> data;
	m.map.reset(new strx::Map(name, data));
}
}}

StrxSerialization(strx::EntityMessage)
{
	ar & base_object<strx::Message>(m);
	ar & m.playerSpot;
	ar & m.id;
	ar & m.maxHp;
}}}

StrxSerialization(strx::ResourcesMessage)
{
	ar & base_object<strx::Message>(m);
	ar & m.resources;
}}}

StrxSerialization(strx::CommandMessage)
{
	ar & base_object<strx::Message>(m);
	ar & m.id;
}}}

StrxSerialization(strx::MineAmountMessage)
{
	ar & base_object<strx::CommandMessage>(m);
	ar & m.amount;
}}}

StrxSerialization(strx::ObjectRemovedMessage)
{
	ar & base_object<strx::CommandMessage>(m);
}}}

StrxSerialization(strx::MoveMessage)
{
	ar & base_object<strx::CommandMessage>(m);
	ar & m.coord;
}}}

StrxSerialization(strx::MapMoveMessage)
{
	ar & base_object<strx::CommandMessage>(m);
	ar & m.from;
	ar & m.to;
}}}

StrxSerialization(strx::RealMoveMessage)
{
	ar & base_object<strx::CommandMessage>(m);
	ar & m.coord;
}}}

StrxSerialization(strx::CollectMessage)
{
	ar & base_object<strx::CommandMessage>(m);
	ar & m.coord;
	ar & m.resourceName;
}}}

StrxSerialization(strx::AttackMessage)
{
	ar & base_object<strx::CommandMessage>(m);
	ar & m.targetId;
}}}

StrxSerialization(strx::HpMessage)
{
	ar & base_object<strx::CommandMessage>(m);
	ar & m.hp;
}}}
