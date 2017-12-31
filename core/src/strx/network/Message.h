#pragma once

#include <nya/enum.hpp>
#include <Strategix_fwd.h>
#include "NetworkCommon.h"

namespace strx
{
struct Message : boost::noncopyable
{
#   define MessageTypeEnumDef(K, V) \
	    K(VECTOR) \
	    K(CONTEXT) \
	    K(START) \
	    K(GAME) \
	    K(PLAYER) \
	    K(MAP) \
	    K(ENTITY) \
	    K(RESOURCES) \
	    K(MINE) \
	    K(MINE_REMOVED)
	nya_enum(Type, MessageTypeEnumDef)

	virtual ~Message() = default;
	virtual Type GetType() const = 0;

	static s_p<Message> Parse(const string& buffer);
	static void Serialize(s_p<Message> message, string& buffer);
};

struct EmptyMessage : Message
{
	Type type;

	EmptyMessage() = default;
	EmptyMessage(Type type) : type(type) {}

	Type GetType() const override { return type; }
};

struct MessageVector : Message, vector<s_p<Message>>
{
	Type GetType() const override { return Type::VECTOR; }
};

struct ContextMessage : Message
{
	ResourceInfosType resourceInfos;

	ContextMessage() = default;
	ContextMessage(const ResourceInfosType& resourceInfos) : resourceInfos(resourceInfos) {}
	Type GetType() const override { return Type::CONTEXT; }
};

struct GameMessage : Message
{
	int id;
	bool started;
	string mapName;
	string creatorName;

	GameMessage() = default;
	GameMessage(const GameMessage& other)
	    : id(other.id), started(other.started), mapName(other.mapName), creatorName(other.creatorName) {}
	GameMessage(int id, bool started, string mapName, string creatorName)
	    : id(id), started(started), mapName(move(mapName)), creatorName(move(creatorName)) {}
	Type GetType() const override { return Type::GAME; }
};

struct PlayerMessage : Message
{
	int gameId;
	int id;
	PlayerType type;
	string name;
	string race;

	PlayerMessage() = default;
	PlayerMessage(int gameId, int id, PlayerType type, string name, string race)
	    : gameId(gameId), id(id), type(type), name(move(name)), race(move(race)) {}
	Type GetType() const override { return Type::PLAYER; }
};

struct MapMessage : Message
{
	s_p<Map> map;

	MapMessage() = default;
	MapMessage(s_p<Map>& map) : map(map) {}
	Type GetType() const override { return Type::MAP; }
};

struct EntityMessage : Message
{
	int playerId;
	IdType id;

	EntityMessage() = default;
	EntityMessage(int playerId, IdType id) : playerId(playerId), id(id) {}
	Type GetType() const override { return Type::ENTITY; }
};

struct ResourcesMessage : Message
{
	ResourcesMessage() = default;
	Type GetType() const override { return Type::RESOURCES; }
};

struct MineMessage : Message
{
	MineMessage() = default;
	Type GetType() const override { return Type::MINE; }
};

struct MineRemovedMessage : Message
{
	MineRemovedMessage() = default;
	Type GetType() const override { return Type::MINE_REMOVED; }
};
}
