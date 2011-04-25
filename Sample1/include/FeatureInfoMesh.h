/* 
 * File:   FeatureInfoMesh.h
 * Author: Akela1101
 *
 * Created on 21 Апрель 2011 г., 15:03
 */

#ifndef _FEATUREINFOMESH_H
#define	_FEATUREINFOMESH_H

#include "FeatureInfoMesh.h"

#include <string>


namespace Sample1
{
	using namespace std;

	struct FeatureInfoIdleMesh : FeatureInfoIdle
	{
		string animation;
		//
		virtual ~FeatureInfoIdleMesh() {}
	};
}

#endif	/* _FEATUREINFOMESH_H */

