/* 
 * File:   TechTreeBuilderFromXml.cpp
 * Author: Akela1101
 * 
 * Created on 12 Март 2010 г., 18:37
 */

#include "TechTreeBuilderFromXml.h"
#include "TechTree.h"
#include "Exception.h"

#include <boost/foreach.hpp>
#include "boost/smart_ptr.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace Strategix;
using namespace boost::property_tree;

#define foreach		BOOST_FOREACH


void TechTreeBuilderFromXml::Build(TechTree *p_tech_tree)
{
	this->p_tech_tree = p_tech_tree;
	ptree pt;

	string file_path = "xml/Races/";
	file_path += p_tech_tree->GetRaceName();
	file_path += ".xml";

	try
	{
		read_xml(file_path, pt);
	}
	catch( const xml_parser_error & )
	{
		cerr << "Can't parse file: " << file_path << endl;
		throw;
	}

	foreach(ptree::value_type &v, pt.get_child("race.entities"))
	{
		BuildEntity(v.second);
	}
}

void TechTreeBuilderFromXml::BuildEntity(const ptree &entity_pt)
{
	shared_ptr<EntityInfo> shpEntityInfo(new EntityInfo);
	shpEntityInfo->name = entity_pt.get<string>("name");
	if( shpEntityInfo->name.length() == 0 )
		throw STRAX_ERROR("One of entities has no name");

	shpEntityInfo->kind = entity_pt.get<string>("kind");

	p_tech_tree->AddNode(shpEntityInfo);
}