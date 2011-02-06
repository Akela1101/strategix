/* 
 * File:   TechTreesBuilderFromXml.cpp
 * Author: Akela1101
 * 
 * Created on 12 Март 2010 г., 18:37
 */

#include "Nya.hpp"
#include "TechTreesBuilderFromXml.h"
#include "TechTree.h"
#include "Exception.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace Strategix;
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
				throw STRATEGIX_ERROR( string("Can't parse file: ") + p.string() );
			}

			BuildRace(p.stem(), propTree);
		}
	}
}

void TechTreesBuilderFromXml::BuildRace(const string &raceName, const pt::ptree &propTree)
{
	sh_p<TechTree> techTree(new TechTree(raceName));

	foreach( const pt::ptree::value_type &v, propTree.get_child("race.entities") )
	{
		BuildEntity(techTree, v.second);
	}

	pTechTrees->insert(TechTreesType::value_type(raceName, techTree));
}

void TechTreesBuilderFromXml::BuildEntity(sh_p<TechTree> techTree, const pt::ptree &entityPropTree)
{
	sh_p<EntiInfo> entityInfo(new EntiInfo);

	entityInfo->name = entityPropTree.get<string>("name");
	entityInfo->kind = entityPropTree.get<string>("kind");

	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("resources") )
	{
		const pt::ptree &resLeaf = v.second; // gold or something else
		entityInfo->resources[v.first] = resLeaf.get_value<ResType>();
	}

	entityInfo->params.hp = entityPropTree.get<HpType>("params.hp");

	if( entityPropTree.get_child("depends").size() )
	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("depends", pt::ptree()) ) // Empty if no depends
	{
		const pt::ptree &dependLeaf = v.second; // name
		entityInfo->depends.push_back( dependLeaf.get_value<string>() );
	}

	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("provides", pt::ptree()) ) // Empty if no provides
	{
		const pt::ptree &provideLeaf = v.second; // name
		entityInfo->provides.push_back( provideLeaf.get_value<string>() );
	}

	entityInfo->file = entityPropTree.get<string>("file");
	entityInfo->scale = entityPropTree.get<float>("scale");

	foreach( const pt::ptree::value_type &v, entityPropTree.get_child("actions", pt::ptree()) ) // Empty if no actions
	{
		const pt::ptree &actionLeaf = v.second; // action
		const string &actionName = actionLeaf.get<string>("name");
		Action &action = entityInfo->actions[actionName]; // add new action to Info
		
		action.name = actionName;
		foreach( const pt::ptree::value_type &v, actionLeaf.get_child("features", pt::ptree()) ) // Empty if no features
		{
			const pt::ptree &featureLeaf = v.second;
			action.features[v.first] = featureLeaf.get_value<FeatureType>();
		}
	}
	
	techTree->AddNode(entityInfo);

	// U can catch( ptree_error == ptree_bad_path || ptree_bad_data )
	// in place of setting default value
}