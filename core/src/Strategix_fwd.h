#pragma once

#include <nya/api.hpp>

namespace strx
{
class Client;
class Entity;
class EntityInfo;
class EntitySlot;
class MapEntity;
class Feature;
class FeatureInfo;
class FeatureInfoCollect;
class FeatureInfoMove;
class FeatureInfoHealth;
class FeatureInfoAttack;
class Game;
class GameSlot;
class Map;
class MapManager;
class MapObject;
class MapPath;
class Message;
class PathFinder;
class MapMine;
class Player;
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
