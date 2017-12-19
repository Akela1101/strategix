#ifndef STRATEGIX_FORWARD_H
#define	STRATEGIX_FORWARD_H

#include <nya/api.hpp>
#include <boost/range/irange.hpp>

namespace strx
{
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
	class Map;
	class MapManager;
	class MapObject;
	class MapPath;
	class PathFinder;
	class MapMine;
	class Player;
	class PlayerSlot;
	class TechTree;
	class TechTreesBuilder;
	class Terrain;

	using namespace std; // only in my namespace, so it won't affect foreign headers
}

#include <strx/common/CoordStructs.h>
#include <strx/common/Resources.h>
#include <strx/common/StrategixCommon.h>

#endif	/* STRATEGIX_FORWARD_H */

