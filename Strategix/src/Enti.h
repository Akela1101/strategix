/* 
 * File:   Enti.h
 * Author: Akela1101
 *
 * Created on 4 Февраль 2011 г., 18:41
 */

#ifndef _ENTI_H
#define	_ENTI_H

#include "StrategixCommon.h"
#include "CoordStructs.h"

#include <map>
#include <list>
#include <string>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;

	class Unit;
	class Player;
	class EntiInfo;
	class FeatureInfo;
	class Feature;
	class FeatureMove;
	
	class Enti
	{
		friend class Feature;
		friend class FeatureMove;

	public:
		Unit *unit;
		Player *player; // Link to owner
		const EntiInfo *entityInfo; // Link to tree

		RealCoord coord;

	private:
		typedef map<string, sh_p<Feature> > FeaturesType;
		FeaturesType features;

		list<Feature*> tickFeatures; // if they become too many, change to set<>

	public:
		Enti(const EntiInfo *entityInfo, const MapCoord &mapCoord); // for RealCoord ???
		virtual ~Enti();

		void Tick(const float seconds);
		bool Move(const RealCoord newCoord);

	private:
		Enti(const Enti &_c);
		Enti& operator =(const Enti &_c);

		Feature* GetFeature(const string &name);
		sh_p<Feature> CreateFeature(const string &name, const FeatureInfo *featureInfo);
	};
}
#endif	/* _ENTI_H */

