/* 
 * File:   KernelBase.cpp
 * Author: Akela1101
 * 
 * Created on 13 Февраль 2010 г., 23:19
 */

#include "Resources.h"
#include "ConfigurationBuilder.h"
#include "TechTreesBuilder.h"
#include "StrategixError.h"

#include <boost/filesystem.hpp>

#include "KernelBase.h"


namespace Strategix
{
	using namespace std;
	using namespace boost;	
	namespace fs = boost::filesystem;


void KernelBase::Configure(sh_p<ConfigurationBuilder> configurationBuilder,
		sh_p<TechTreesBuilder> techTreesBuilder)
{
	configurationBuilder->Build(&resourceInfos);
	techTreesBuilder->Build(&techTrees);
}

sh_p<vector<string> > KernelBase::GetMapNames()
{
	sh_p<vector<string> > mapNames(new vector<string>());

	fs::recursive_directory_iterator it("Maps/"), eod;
	foreach( const fs::path &p, std::make_pair(it, eod) )
	{
		if( fs::is_regular_file(p) && fs::extension(p) == ".map" )
		{
			mapNames->push_back(p.stem().string());
		}
	}
	return mapNames;
}

sh_p<vector<string> > KernelBase::GetRaceNames()
{
	sh_p<vector<string> > raceNames(new vector<string>());

	foreach( const TechTreesType::value_type &tt_pair, techTrees )
	{
		raceNames->push_back(tt_pair.second->raceName);
	}
	return raceNames;
}

Resource KernelBase::MakeResource(const string name, const float amount)
{
	ResourceInfosType::iterator iRi = resourceInfos.find(name);
	if( iRi == resourceInfos.end() )
	{
		STRATEGIX_ERROR("There is no resource named: " + name);
	}
	return Resource(iRi->first, amount);
}

sh_p<Resources> KernelBase::MakeResources()
{
	sh_p<Resources> resourses(new Resources);
	foreach( const ResourceInfosType::value_type &ri, resourceInfos )
	{
		resourses->values.insert(make_pair(ri.first, 0));
	}
	return resourses;
}

}