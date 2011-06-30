/* 
 * File:   KernelBase.h
 * Author: Akela1101
 *
 * Created on 13 Февраль 2010 г., 23:19
 */

#ifndef _KERNELBASE_H
#define	_KERNELBASE_H

#include "StrategixSingleton.h"
#include "TechTree.h"
#include "ResourceInfo.h"

#include <string>
#include <map>
#include <vector>

#include "Strategix_Forward.h"


namespace Strategix
{
	using namespace std;
	using namespace boost;


	class KernelBase : public StrategixSingleton<KernelBase>
	{
	private:
		TechTreesType techTrees;
		ResourceInfosType resourceInfos;

	public:	
		// Call before initialize Kernel!
		void Configure(sh_p<ConfigurationBuilder> configurationBuilder,
				sh_p<TechTreesBuilder> techTreesBuilder);
		
		// GET
		sh_p<vector<string> > GetMapNames();
		sh_p<vector<string> > GetRaceNames();		
		const ResourceInfo& GetResourceInfo(const string name) { return *resourceInfos[name]; }

		// MAKE
		sh_p<TechTree> MakeTechTreeCopy(const string raceName) { return sh_p<TechTree>(new TechTree(*techTrees[raceName])); }
		Resource MakeResource(const string name, const float amount);
		sh_p<Resources> MakeResources(); // filled with zero
	};
}

#endif	/* _KERNELBASE_H */

