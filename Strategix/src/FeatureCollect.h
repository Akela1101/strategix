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

#include "Strategix_Forward.h"


namespace Strategix
{
	class FeatureCollect : public Feature, public ICommand
	{
	protected:
		const FeatureInfoCollect *featureInfoCollect; // Link to tree
		float capacity; // amount of resource Enti can hold
		std::string resourceName;
		
	private:
		float load; // amount of resource Enti is holding
		sh_p<MapResource> mapResource; // target		
		bool isMovingToCollector;

	public:
		FeatureCollect(const FeatureInfo *featureInfo, Enti *enti);		
		
		bool Collect(sh_p<MapResource> mapResource);
		virtual bool Tick(const float seconds);
		virtual void Stop();

		virtual void OnComplete(bool isComplete); // Moving Complete

	protected:
		Enti* FindCollector(); // resource collector
		void MoveToCollector(); // going back to base(or other collector)
			
	private:
		FeatureCollect(const FeatureCollect &_c);
		FeatureCollect& operator =(const FeatureCollect &_c);
	};
}

#endif	/* _FEATURECOLLECT_H */

