/* 
 * File:   FeatureCollect.h
 * Author: Akela1101
 *
 * Created on 18 Май 2011 г., 14:48
 */

#ifndef _FEATURECOLLECT_H
#define	_FEATURECOLLECT_H

#include "Feature.h"
#include "Interfaces.h"
#include "Map.h"

#include "Nya.hpp"


namespace Strategix
{
	class FeatureInfoCollect;

	class FeatureCollect : public Feature, public IMove
	{
	protected:
		const FeatureInfoCollect *featureInfoCollect; // Link to tree
		const ResType capacity; // always = featureInfoCollect->capacity
		
	private:		
		float load; // Amount of resource Enti is holding, load must be float to avoid loses
		w_p<MapResource> mapResource; // target
		Enti *collector; // where to take resources to

	public:
		FeatureCollect(const FeatureInfo *featureInfo, Enti *enti);
		virtual ~FeatureCollect() {}
		
		bool Collect(sh_p<MapResource> mapResource);
		bool Tick(const float seconds);

		virtual void OnMoveStart();
		virtual void OnMove();
		virtual void OnMoveStop();
			
	private:
		FeatureCollect(const FeatureCollect &_c);
		FeatureCollect& operator =(const FeatureCollect &_c);
	};
}

#endif	/* _FEATURECOLLECT_H */

