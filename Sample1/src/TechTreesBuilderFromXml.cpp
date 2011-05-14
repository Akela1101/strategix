/* 
 * File:   TechTreesBuilderFromXml.cpp
 * Author: Akela1101
 * 
 * Created on 12 Март 2010 г., 18:37
 */

#include "EntiInfoMesh.h"
#include "FeatureInfo.h"
#include "TechTree.h"
#include "StrategixError.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

#include "TechTreesBuilderFromXml.h"


namespace Sample1
{
	using namespace Strategix;
	using namespace std;
	using namespace boost;
	namespace pt = boost::property_tree;
	namespace fs = boost::filesystem;


void TechTreesBuilderFromXml::Build(TechTreesType *pTechTrees)
{
	this->pTechTrees = pTechTrees;

	fs::recursive_directory_iterator it("xml/Races/"), eod;
	foreach( const fs::path &p, std::make_pair(it, eod) )
	{
		if( fs::is_regular_file(p) && fs::extension(p) == ".xml" )
		{
			pt::ptree propTree;

			try
			{
				pt::read_xml(p.string(), propTree);
			}
			catch( const pt::xml_parser_error & )
			{
				STRATEGIX_ERROR( string("Can't parse file: ") + p.string() );
			}

			BuildRace(p.stem().string(), propTree.get_child("race"));
		}
	}
}

void TechTreesBuilderFromXml::BuildRace(const string &raceName, const pt::ptree &propTree)
{
	sh_p<TechTree> techTree(new TechTree(raceName));

	techTree->mainBuildingName = propTree.get<string>("main_building");

	foreach( const pt::ptree::value_type &v, propTree.get_child("entities") )
	{
		BuildEntity(techTree, v.second);
	}

	pTechTrees->insert(TechTreesType::value_type(raceName, techTree));
}

void TechTreesBuilderFromXml::BuildEntity(sh_p<TechTree> techTree, const pt::ptree &entityPropTree)
{
	sh_p<EntiInfoMesh> eim(new EntiInfoMesh);

	eim->name = entityPropTree.get<string>("name");
	eim->kind = entityPropTree.get<string>("kind");

/*
	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("resources") )
	{
		const pt::ptree &resLeaf = v.second; // gold or something else
		eim->resources[v.first] = resLeaf.get_value<ResType>();
	}

	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("depends", pt::ptree()) ) // Empty if no depends
	{
		const pt::ptree &dependLeaf = v.second; // name
		eim->depends.push_back( dependLeaf.get_value<string>() );
	}

	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("provides", pt::ptree()) ) // Empty if no provides
	{
		const pt::ptree &provideLeaf = v.second; // name
		eim->provides.push_back( provideLeaf.get_value<string>() );
	}
*/
	eim->meshName = entityPropTree.get<string>("mesh");
	eim->meshScale = entityPropTree.get<float>("scale");

	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("features", pt::ptree()) ) // Empty if no features
	{
		const string &featureName = v.first;
		const pt::ptree &feature = v.second;
		
		try
		{
			if( featureName == "move" )
			{
				eim->featureInfos[featureName].reset(new FeatureInfoMove(feature.get<float>("speed")));
			}
		}
		catch(pt::ptree_error){}
	}

	techTree->AddNode(eim);

	// U can catch( ptree_error == ptree_bad_path || ptree_bad_data )
	// in place of setting default value
}

}