#ifndef STRATEGIX_FORWARD_H
#define	STRATEGIX_FORWARD_H

#include <nya/api.hpp>
#include <boost/range/irange.hpp>

namespace strx
{
	class Enti;
	class EntiInfo;	
	class EntiSlot;	
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
	class MapsPath;
	class MapsPathsFinder;
	class Mine;
	class Player;
	class PlayerSlot;
	class Resources;
	class TechTree;
	class TechTreesBuilder;

	using namespace std; // only in my namespace, so it won't affect foreign headers
}

#include <strx/common/CoordStructs.h>
#include <strx/common/Resource.h>
#include <strx/common/StrategixCommon.h>

#endif	/* STRATEGIX_FORWARD_H */

