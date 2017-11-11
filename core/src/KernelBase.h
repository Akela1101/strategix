#ifndef _KERNELBASE_H
#define    _KERNELBASE_H

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

class KernelBase : public StrategixSingleton<KernelBase>
{
private:
	TechTreesType techTrees;
	ResourceInfosType resourceInfos;

public:
	// Call before initialize Kernel!
	void Configure(
			s_p<ConfigurationBuilder> configurationBuilder, s_p<TechTreesBuilder> techTreesBuilder);
	
	// GET
	s_p<vector<string>> GetMapNames();
	s_p<vector<string>> GetRaceNames();
	
	s_p<const ResourceInfo> GetResourceInfo(const string name) const
	{
		auto iRi = resourceInfos.find(name);
		return iRi != resourceInfos.end() ? iRi->second : s_p<const ResourceInfo>();
	}
	
	// MAKE
	s_p<TechTree> MakeTechTreeCopy(const string raceName)
	{ return s_p<TechTree>(new TechTree(*techTrees[raceName])); }
	
	Resource MakeResource(string name, float amount);
	s_p<Resources> MakeResources(); // filled with zero
	s_p<Resources> MakeResources(const ResourcesAllType& values);
};
}

#endif    /* _KERNELBASE_H */

