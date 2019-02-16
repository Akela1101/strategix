#pragma once

#include <nya/enum.hpp>
#include <Strategix_fwd.h>

namespace strx
{
struct Message : boost::noncopyable
{
#   define MessageTypeEnumDef(K, V) \
	    K(VECTOR)          /* vector of messages */ \
	    K(COMMAND)         /* command to entity */ \
	    K(EXIT)            /* exit from client */ \
	    K(CONTEXT)         /* game context */ \
	    K(START)           /* start game */ \
	    K(GAME)            /* game description */ \
	    K(PLAYER)          /* player description */ \
	    K(MAP)             /* map description */ \
	    K(ENTITY)          /* entity description */ \
	    K(RESOURCES)       /* player resources */ \
	    K(MINE_AMOUNT)     /* mine amount changed */ \
	    K(OBJECT_REMOVED)  /* object removed */ \
	    K(MOVE)            /* entity map placing change */ \
	    K(REAL_MOVE)       /* entity precise coordinate move */ \
	    K(COLLECT)         /* collect mine */ \
	    K(ATTACK)          /* attack other entity */ \
	    K(HP)              /* hit points change */
	nya_enum(Type, MessageTypeEnumDef)

	virtual ~Message() = default;
	virtual Type GetType() const = 0;

	static s_p<Message> Parse(const string& buffer);
	static void Serialize(s_p<Message> message, string& buffer);
};

struct MessageVector : Message, vector<s_p<Message>>
{
	Type GetType() const override { return Type::VECTOR; }
};

struct EmptyMessage : Message
{
	Type type;

	EmptyMessage() = default;
	EmptyMessage(Type type) : type(type) {}

	Type GetType() const override { return type; }
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
	GameId gameId;
	PlayerType type;
	int spot;
	string name;
	string race;

	PlayerMessage() = default;
	PlayerMessage(GameId gameId, PlayerType type)
	    : gameId(gameId), type(type) {}
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
	int playerSpot;
	IdType id;
	HpType maxHp;

	EntityMessage() = default;
	EntityMessage(int playerSpot, IdType id, HpType maxHp)
	    : playerSpot(playerSpot), id(id), maxHp(maxHp) {}
	Type GetType() const override { return Type::ENTITY; }
};

struct ResourcesMessage : Message
{
	Resources resources;

	ResourcesMessage() = default;
	ResourcesMessage(Resources resources) : resources(move(resources)) {}
	Type GetType() const override { return Type::RESOURCES; }
};

struct CommandMessage : Message
{
	IdType id;

	CommandMessage() = default;
	CommandMessage(IdType id) : id(id) {}
};

struct MineAmountMessage : CommandMessage
{
	ResourceUnit amount;

	MineAmountMessage() = default;
	MineAmountMessage(IdType id, ResourceUnit amount) : CommandMessage(id), amount(amount) {}
	Type GetType() const override { return Type::MINE_AMOUNT; }
};

struct ObjectRemovedMessage : CommandMessage
{
	using CommandMessage::CommandMessage;
	Type GetType() const override { return Type::OBJECT_REMOVED; }
};

struct MoveMessage : CommandMessage
{
	MapCoord coord;

	MoveMessage() = default;
	MoveMessage(IdType id, MapCoord coord) : CommandMessage(id), coord(coord) {}
	Type GetType() const override { return Type::MOVE; }
};

struct MapMoveMessage : CommandMessage
{
	MapCoord from;
	MapCoord to;

	MapMoveMessage() = default;
	MapMoveMessage(IdType id, MapCoord from, MapCoord to) : CommandMessage(id), from(from), to(to) {}
	Type GetType() const override { return Type::MOVE; }
};

struct RealMoveMessage : CommandMessage
{
	RealCoord coord;

	RealMoveMessage() = default;
	RealMoveMessage(IdType id, RealCoord coord) : CommandMessage(id), coord(coord) {}
	Type GetType() const override { return Type::REAL_MOVE; }
};

struct CollectMessage : CommandMessage
{
	MapCoord coord;
	string resourceName;

	CollectMessage() = default;
	CollectMessage(IdType id, MapCoord coord, string resourceName)
	    : CommandMessage(id), coord(coord), resourceName(move(resourceName)) {}
	Type GetType() const override { return Type::COLLECT; }
};

struct AttackMessage : CommandMessage
{
	IdType targetId;

	AttackMessage() = default;
	AttackMessage(IdType id, IdType targetId) : CommandMessage(id), targetId(targetId) {}
	Type GetType() const override { return Type::ATTACK; }
};

struct HpMessage : CommandMessage
{
	HpType hp;

	HpMessage() = default;
	HpMessage(IdType id, HpType hp) : CommandMessage(id), hp(hp) {}
	Type GetType() const override { return Type::HP; }
};

}
