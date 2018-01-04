#pragma once

#include <nya/api.hpp>

namespace strx
{
class Cell;
class Client;
class CommandMessage;
class Entity;
class EntityInfo;
class EntityMessage;
class EntitySlot;
class Feature;
class FeatureInfo;
class FeatureInfoCollect;
class FeatureInfoMove;
class FeatureInfoHealth;
class FeatureInfoAttack;
class Game;
class GameMessage;
class GameSlot;
class Map;
class MapEntity;
class MapManager;
class MapMessage;
class MapObject;
class MapPath;
class Message;
class MapMine;
class PathFinder;
class Player;
class PlayerMessage;
class PlayerSlot;
class Server;
class TechTree;
class TechTreesBuilder;
class Terrain;

using namespace std; // only in my namespace, so it won't affect foreign headers
}

#include <strx/common/CoordStructs.h>
#include <strx/common/Resources.h>
#include <strx/common/StrategixCommon.h>
