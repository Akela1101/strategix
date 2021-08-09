#pragma once

#include <nya/api.hpp>

namespace strx
{
struct AttackFeatureInfo;
struct Cell;
struct CollectFeatureInfo;
struct CommandMessage;
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
class MapManager;
class MapPath;
class PathFinder;
class PlayerKernel;
class Player;
class Server;
class TechTree;
class TechTreesBuilder;
class User;

using namespace std;  // only in my namespace, so it won't affect foreign headers
}  // namespace strx

#include "CoordStructs.hpp"
#include "Resources.hpp"
#include "strx_common.hpp"
