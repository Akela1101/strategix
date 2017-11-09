/* 
 * File:   KernelBase.cpp
 * Author: Akela1101
 * 
 * Created on 13 Февраль 2010 г., 23:19
 */

#include "Resources.h"
#include "ConfigurationBuilder.h"
#include "TechTreesBuilder.h"

#include <boost/filesystem.hpp>

#include "KernelBase.h"


namespace Strategix
{
using namespace std;
using namespace boost;
namespace fs = boost::filesystem;


void KernelBase::Configure(
		s_p<ConfigurationBuilder> configurationBuilder, s_p<TechTreesBuilder> techTreesBuilder)
{
	configurationBuilder->Build(&resourceInfos);
	techTreesBuilder->Build(&techTrees);
}

s_p<vector<string>> KernelBase::GetMapNames()
{
	s_p<vector<string>> mapNames(new vector<string>());
	
	fs::recursive_directory_iterator it("Maps/"), eod;
	for (; it != eod; ++it)
	{
		const fs::path& p = *it;
		if (fs::is_regular_file(p) && fs::extension(p) == ".map")
		{
			mapNames->push_back(p.stem().string());
		}
	}
	return mapNames;
}

s_p<vector<string>> KernelBase::GetRaceNames()
{
	s_p<vector<string>> raceNames(new vector<string>());
	
	for (const TechTreesType::value_type& tt_pair : techTrees)
	{
		raceNames->push_back(tt_pair.second->raceName);
	}
	return raceNames;
}

Resource KernelBase::MakeResource(const string name, const float amount)
{
	auto iRi = resourceInfos.find(name);
	if (iRi == resourceInfos.end())
	{
		STRATEGIX_EXCEPTION("There is no resource named: " + name);
	}
	return Resource(iRi->first, amount);
}

s_p<Resources> KernelBase::MakeResources()
{
	s_p<Resources> resourses(new Resources);
	for (const ResourceInfosType::value_type& ri : resourceInfos)
	{
		resourses->values.insert(make_pair(ri.first, 0));
	}
	return resourses;
}

s_p<Resources> KernelBase::MakeResources(const ResourcesAllType& values)
{
	s_p<Resources> resourses(new Resources);
	resourses->values = values;
	return resourses;
}

}