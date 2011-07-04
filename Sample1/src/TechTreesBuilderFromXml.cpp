/* 
 * File:   TechTreesBuilderFromXml.cpp
 * Author: Akela1101
 * 
 * Created on 12 Март 2010 г., 18:37
 */

#include "EntiInfoMesh.h"

#include <Strategix.h>
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
				STRATEGIX_ERROR( "Can't parse file: " + p.string() );
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
		techTree->AddNode(BuildEntity(v.second));
	}

	pTechTrees->insert(std::make_pair(raceName, techTree));
}

sh_p<EntiInfoMesh> TechTreesBuilderFromXml::BuildEntity(const pt::ptree &entityPropTree)
{
	sh_p<EntiInfoMesh> eim(new EntiInfoMesh);

	eim->name = entityPropTree.get<string>("name");
	eim->kind = entityPropTree.get<string>("kind");

	eim->meshName = entityPropTree.get<string>("mesh");
	eim->meshScale = entityPropTree.get<float>("scale");
	
	eim->resources = BuildResources(entityPropTree.get_child("resources"));
/*
	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("depends", pt::ptree()) ) // Empty if no depends
	{
		const pt::ptree &depend = v.second; // name
		eim->depends.push_back( depend.get_value<string>() );
	}

	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("provides", pt::ptree()) ) // Empty if no provides
	{
		const pt::ptree &provide = v.second; // name
		eim->provides.push_back( provide.get_value<string>() );
	}
*/	

	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("features", pt::ptree()) ) // Empty if no features
	{
		const string &featureName = v.first;
		const pt::ptree &feature = v.second;
		
		try
		{
			if( featureName == "move" )
			{
				const float speed = feature.get<float>("speed");
				eim->featureInfos[featureName].reset(new FeatureInfoMove(speed));
			}
			else if( featureName == "collect" )
			{
				const float speed = feature.get<float>("speed");
				const float radius = feature.get<float>("radius");				
				sh_p<Resources> capacities = BuildResources(feature.get_child("capacities"));
				eim->featureInfos[featureName].reset(new FeatureInfoCollect(speed, radius, capacities));
			}
			else if( featureName == "health" )
			{
				const float hp = feature.get<HpType>("hp");
				const float regenSpeed = feature.get<float>("regenSpeed");
				eim->featureInfos[featureName].reset(new FeatureInfoHealth(hp, regenSpeed));
			}
			else if( featureName == "attack" )
			{
				const float damage = feature.get<HpType>("damage");
				const float speed = feature.get<float>("speed");
				eim->featureInfos[featureName].reset(new FeatureInfoAttack(damage, speed));
			}
		}
		catch(pt::ptree_error){}
	}
	return eim;
	// U can catch( ptree_error == ptree_bad_path || ptree_bad_data )
	// in place of setting default value
}

sh_p<Resources> TechTreesBuilderFromXml::BuildResources(const pt::ptree &resourcesPropTree)
{
	ResourcesAllType values;
	foreach( const pt::ptree::value_type &v, resourcesPropTree )
	{
		const string &resourceName = v.first; // gold or something else
		if( !KernelBase::GS().GetResourceInfo(resourceName) )
			STRATEGIX_ERROR("Wrong resource type in one of Races: " + resourceName +
			                "\nCheck configuration file.");

		const pt::ptree &resource = v.second;
		values.insert(make_pair(resourceName, resource.get_value<float>()));
	}
	return KernelBase::GS().MakeResources(values);
}

}