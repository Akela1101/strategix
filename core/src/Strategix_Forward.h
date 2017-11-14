#ifndef STRATEGIX_FORWARD_H
#define	STRATEGIX_FORWARD_H

#include <CoordStructs.h>
#include <StrategixCommon.h>
#include <memory>
#include <nya/exceptoin.hpp>
#include <nya/log.hpp>
#include <nya.hpp>


namespace Strategix
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
	class MapResource;
	class MapsPath;
	class MapsPathsFinder;
	class Player;
	class PlayerSlot;
	class ResourceInfo;
	class Resources;
	class TechTree;
	class TechTreesBuilder;

	using ResourceInfosType = std::map<std::string, u_p<ResourceInfo>>;
	using TechTreesType = map<string, u_p<TechTree>>;
}

#endif	/* STRATEGIX_FORWARD_H */

