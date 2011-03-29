/* 
 * File:   KernelBase.h
 * Author: Akela1101
 *
 * Created on 13 Февраль 2010 г., 23:19
 */

#ifndef _KERNELBASE_H
#define	_KERNELBASE_H

#include "TechTree.h"
#include "StrategixSingleton.h"
#include "StrategixCommon.h"

#include <string>
#include <vector>


namespace Strategix
{
	using namespace std;
	using namespace boost;

	class KernelBase : public StrategixSingleton<KernelBase>
	{
	public:
		TechTreesType techTrees;

	public:
		KernelBase();
		virtual ~KernelBase();

		sh_p<vector<string> > GetMapNames();
		sh_p<vector<string> > GetRaceNames();
		const float GetTileSize() { return tileSize; }
	};
}

#endif	/* _KERNELBASE_H */

