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

	typedef std::map<std::string, sh_p<ResourceInfo> > ResourceInfos;

	class KernelBase : public StrategixSingleton<KernelBase>
	{
	private:
		TechTreesType techTrees;
		
		ResourceInfos resourceInfos;

	public:
		// These functions are called before initialize Kernel!
		void Configure(const string configFileName);
		void BuildTechTrees(sh_p<TechTreesBuilder> techTreesBuilder);
		
		// GET
		sh_p<vector<string> > GetMapNames();
		sh_p<vector<string> > GetRaceNames();
		const TechTree& GetTechTree(const string raceName) { return *techTrees[raceName]; }
		const ResourceInfo& GetResourceInfo(const string resourceName) { return *resourceInfos[resourceName]; }
		const ResourceInfos& GetResourceInfos() { return resourceInfos; }
	};
}

#endif	/* _KERNELBASE_H */

