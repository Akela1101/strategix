/* 
 * File:   Enti.h
 * Author: Akela1101
 *
 * Created on 4 Февраль 2011 г., 18:41
 */

#ifndef _ENTI_H
#define	_ENTI_H

#include "FeatureMove.h"
#include "FeatureCollect.h"

#include <map>
#include <list>
#include <string>
#include <typeinfo>

#include "Strategix_Forward.h"


namespace Strategix
{
	using namespace std;
	
	class Enti
	{
	public:
		EntiSlot *entiSlot; // Link to entiSlot
		Player *player; // Link to owner
		const EntiInfo *entityInfo; // Link to tree
		RealCoord coord; // real coordinate

	private:		
		typedef map<string, sh_p<Feature> > FeaturesType;
		FeaturesType features; // map[typeid.name]

		Feature* tickFeature; // current active feature getting Tick
		list<Feature*> passiveTickFeatures; // features not interfering with tickFeature
		/* ex.: regeneration, taking damage, etc. */

		bool isLastFeature; // check if there is no new tickFeature before remove it

	public:
		Enti(const EntiInfo *entityInfo, const RealCoord &coord);
		
		void Tick(const float seconds);
		void AssignTickFeature(Feature *feature, bool isPassive = false);

		template<typename F> F* Do() // get feature with type F
		{
			const string featureName = typeid(F).name();
			FeaturesType::iterator iFeature = features.find(featureName);
			if( iFeature != features.end() )
			{
				return dynamic_cast<F*>(iFeature->second.get());
			}
			STRATEGIX_ERROR(string("There is no feature named: ") + featureName);
			return 0;
		}

	private:
		Enti(const Enti &_c);
		Enti& operator =(const Enti &_c);

		void AddFeature(const string &name, const FeatureInfo *featureInfo);
	};
}
#endif	/* _ENTI_H */

