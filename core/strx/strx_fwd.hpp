#pragma once

#include <nya/api.hpp>

#include "CoordStructs.hpp"
#include "Resources.hpp"

namespace strx
{
using namespace std;  // only in strx namespace, so it won't affect foreign headers

struct AttackFeatureInfo;
struct Cell;
struct CollectFeatureInfo;
struct CommandMessage;
struct ContextMessage;
struct EntityInfo;
struct EntityMessage;
struct FeatureInfo;
struct GameMessage;
struct HealthFeatureInfo;
struct MapEntity;
struct MapObject;
struct MapMessage;
struct MapMine;
struct Message;
struct MoveFeatureInfo;
struct PlayerMessage;
struct Terrain;

class Client;
class EntityKernel;
class Entity;
class Feature;
class GameKernel;
class Game;
class Map;
class MapPath;
class PathFinder;
class PlayerKernel;
class Player;
class Server;
class TechTree;
class User;

using IdType = int;
using HpType = int;
using GameId = int;
using PlayerId = int;
using ResourcesContext = s_p<vector<string>>;
using TechTreesType = umap<string, u_p<TechTree>>;

enum class PlayerType
{
	HUMAN,
	AI
};

struct MapContext
{
	string name;
	int width;
	int height;
	int playersNumber;
};
}  // namespace strx
