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
class Entity;
class EntitySlot;
class Feature;
class Game;
class GameSlot;
class Map;
class MapManager;
class MapPath;
class PathFinder;
class Player;
class PlayerSlot;
class Server;
class TechTree;
class TechTreesBuilder;

using namespace std;  // only in my namespace, so it won't affect foreign headers
}  // namespace strx

#include <strx/common/CoordStructs.h>
#include <strx/common/Resources.h>
#include <strx/common/StrategixCommon.h>
