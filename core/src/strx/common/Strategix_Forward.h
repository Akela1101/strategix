#ifndef STRATEGIX_FORWARD_H
#define	STRATEGIX_FORWARD_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <nya.hpp>
#include <nya/exception.hpp>
#include <nya/log.hpp>


namespace strx
{
	class BaseMap;
	class Enti;
	class EntiInfo;	
	class EntiSlot;	
	class Feature;
	class FeatureInfo;
	class FeatureInfoCollect;
	class FeatureInfoMove;
	class FeatureInfoHealth;
	class FeatureInfoAttack;
	class KernelSlot;
	class Map;
	class MapManager;
	class Mine;
	class MapsPath;
	class MapsPathsFinder;
	class Player;
	class PlayerSlot;
	class Resources;
	class TechTree;
	class TechTreesBuilder;

	using namespace std; // only in my namespace, so it won't affect foreign headers

	using ResourceInfosType = vector<string>;
	using TechTreesType = umap<string, u_p<TechTree>>;
}

#include <strx/common/CoordStructs.h>
#include <strx/common/Resource.h>
#include <strx/common/StrategixCommon.h>

#endif	/* STRATEGIX_FORWARD_H */

