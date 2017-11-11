#include "ResourceInfoMesh.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "ConfigurationBuilderFromXml.h"


namespace Sample1
{
namespace pt = boost::property_tree;

const char configFileName[] = "config/strategix_config.xml";

void ConfigurationBuilderFromXml::Build(ResourceInfosType* pResourceInfos)
{
	pt::ptree propTree;
	pt::read_xml(configFileName, propTree);
	
	for (const pt::ptree::value_type& v : propTree.get_child("resource_types"))
	{
		if (pResourceInfos->find(v.first) != pResourceInfos->end())
		{
			/* Two resources with the same name! */;
		}
		const string meshName = v.second.get<string>("mesh");
		pResourceInfos->insert(make_pair(v.first, new ResourceInfoMesh(v.first, meshName)));
	}
}
}
