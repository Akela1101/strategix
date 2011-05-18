/* 
 * File:   KernelBase.cpp
 * Author: Akela1101
 * 
 * Created on 13 Февраль 2010 г., 23:19
 */

#include "TechTreesBuilder.h"
#include "Log.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>

#include "KernelBase.h"


namespace Strategix
{
	using namespace std;
	using namespace boost;
	namespace pt = boost::property_tree;
	namespace fs = boost::filesystem;

void KernelBase::Configure(const string configFileName)
{
	pt::ptree propTree;
	pt::read_xml(configFileName, propTree);

	int i = 0;
	foreach( const pt::ptree::value_type &v, propTree.get_child("resource_types") )
	{
		const string meshName = v.second.get<string>("mesh");
		resourceInfos[v.first].reset(new ResourceInfo(v.first, meshName, i++));
	}
}

void KernelBase::BuildTechTrees(sh_p<TechTreesBuilder> techTreesBuilder)
{	
	techTreesBuilder->Build(&techTrees);
}

// Checking directory with Maps
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

// Checking TechTree
sh_p<vector<string> > KernelBase::GetRaceNames()
{
	sh_p<vector<string> > raceNames(new vector<string>());

	foreach( const TechTreesType::value_type &tt_pair, techTrees )
	{
		raceNames->push_back(tt_pair.second->raceName);
	}
	return raceNames;
}

}
