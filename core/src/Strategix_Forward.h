#ifndef STRATEGIX_FORWARD_H
#define	STRATEGIX_FORWARD_H

#include <CoordStructs.h>
#include <StrategixCommon.h>
#include <memory>
#include <nya/exception.hpp>
#include <nya/log.hpp>
#include <nya.hpp>


namespace strategix
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
	class KernelSlot;
	class Map;
	class MapFull;
	class MapLocal;
	class Mine;
	class MapsPath;
	class MapsPathsFinder;
	class Player;
	class PlayerSlot;
	class Resources;
	class TechTree;
	class TechTreesBuilder;

	using ResourceInfosType = std::vector<std::string>;
	using TechTreesType = map<string, u_p<TechTree>>;
}

#endif	/* STRATEGIX_FORWARD_H */

