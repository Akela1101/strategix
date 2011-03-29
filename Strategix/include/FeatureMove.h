/* 
 * File:   FeatureMove.h
 * Author: Akela1101
 *
 * Created on 23 Март 2011 г., 16:48
 */

#ifndef _FEATUREMOVE_H
#define	_FEATUREMOVE_H

#include "Feature.h"
#include "CoordStructs.h"


namespace Strategix
{
	class MapsPath;
	
	class FeatureMove : public Feature
	{
		float distance;
		RealCoord direction, finish;
		sh_p<MapsPath> mapsPath;

	public:
		FeatureMove();
		virtual ~FeatureMove();

		virtual void Tick(const float seconds);

		bool operator() (const RealCoord newCoord);
			

	private:
		FeatureMove(const FeatureMove &_c);
		FeatureMove& operator =(const FeatureMove &_c);
	};
}

#endif	/* _FEATUREMOVE_H */

