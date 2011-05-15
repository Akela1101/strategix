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

#include <string>
#include <vector>

#include "Nya.hpp"


namespace Strategix
{
	using namespace std;
	using namespace boost;

	class TechTreesBuilder;

	class KernelBase : public StrategixSingleton<KernelBase>
	{
	private:
		TechTreesType techTrees;

	public:
		// U must call these functions before initialize Kernel!
		void BuildTechTrees(sh_p<TechTreesBuilder> techTreesBuilder);

		// GET
		sh_p<vector<string> > GetMapNames();
		sh_p<vector<string> > GetRaceNames();
		const TechTree& GetTechTree(const string raceName) { return *techTrees[raceName]; }
	};
}

#endif	/* _KERNELBASE_H */

