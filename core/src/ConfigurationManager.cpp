#include <EntiInfo.h>
#include <Kernel.h>
#include <ResourceInfo.h>
#include <TechTree.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>

#include "ConfigurationManager.h"


namespace Strategix::ConfigurationManager
{
using namespace Strategix;
using namespace std;
namespace pt = boost::property_tree;
namespace fs = boost::filesystem;


void ParseConfig(ResourceInfosType* pResourceInfos)
{
	try
	{
		pt::ptree propTree;
		pt::read_xml(Kernel::Get("config_file"), propTree);
		
		for (auto&& name_tree : propTree.get_child("resource_types"))
		{
			const string& resourceName = name_tree.first;
			if (in_(resourceName, *pResourceInfos))
			{
				STRATEGIX_WARNING("Wrong resource type in one of Races: " + resourceName);
			}
			pResourceInfos->insert(make_pair(resourceName, new ResourceInfo(resourceName)));
		}
	}
	catch (exception& e)
	{
		STRATEGIX_ERROR(e.what());
	}
}

u_p<Resources> ParseResources(const pt::ptree& resourcesPropTree)
{
	try
	{
		ResourcesAllType values;
		for (auto&& name_tree : resourcesPropTree)
		{
			const string& resourceName = name_tree.first; // gold or something else
			if (!Kernel::GetResourceInfo(resourceName))
			{
				STRATEGIX_WARNING("Wrong resource type in one of Races: " + resourceName
				                  + "\nCheck configuration file.");
				continue;
			}
			
			const pt::ptree& resource = name_tree.second;
			values.insert(make_pair(resourceName, resource.get_value<float>()));
		}
		return make_u<Resources>(values);
	}
	catch (pt::ptree_error& e)
	{
		STRATEGIX_WARNING(e.what());
		return nullptr;
	}
}

u_p<FeatureInfo> ParseFeature(const string& name, const pt::ptree& feature)
{
	try
	{
		if (name == "move")
		{
			auto speed = feature.get<float>("speed");
			return make_u<FeatureInfoMove>(speed);
		}
		else if (name == "collect")
		{
			auto speed = feature.get<float>("speed");
			auto radius = feature.get<float>("radius");
			s_p<Resources> capacities = ParseResources(feature.get_child("capacities"));
			return make_u<FeatureInfoCollect>(speed, radius, capacities);
		}
		else if (name == "health")
		{
			auto hp = feature.get<HpType>("hp");
			auto regenSpeed = feature.get<float>("regenSpeed");
			return make_u<FeatureInfoHealth>(hp, regenSpeed);
		}
		else if (name == "attack")
		{
			auto damage = feature.get<HpType>("damage");
			auto speed = feature.get<float>("speed");
			return make_u<FeatureInfoAttack>(damage, speed);
		}
	}
	catch (pt::ptree_error& e)
	{
		STRATEGIX_WARNING("Unable to parse feature: " + name + " Error: " + e.what());
		return nullptr;
	}
}

u_p<EntiInfo> ParseEntity(const pt::ptree& entityPropTree)
{
	try
	{
		u_p<EntiInfo> eim(new EntiInfo);
		
		eim->name = entityPropTree.get<string>("name");
		eim->kind = entityPropTree.get<string>("kind");
		eim->resources = ParseResources(entityPropTree.get_child("resources"));
		
		for (auto&& name_tree : entityPropTree.get_child("features", pt::ptree())) // Empty if no features
		{
			const string& name = name_tree.first;
			if (auto&& feature = ParseFeature(name, name_tree.second))
			{
				eim->featureInfos[name] = move(feature);
			}
		}
		return eim;
	}
	catch (pt::ptree_error& e)
	{
		STRATEGIX_WARNING(e.what());
		return nullptr;
	}
}

u_p<TechTree> ParseRace(const string& raceName, const pt::ptree& propTree)
{
	try
	{
		u_p<TechTree> techTree(new TechTree(raceName));
		techTree->mainBuildingName = propTree.get<string>("main_building");
		
		for (auto&& name_tree : propTree.get_child("entities"))
		{
			techTree->AddNode(ParseEntity(name_tree.second));
		}
		return techTree;
	}
	catch (pt::ptree_error& e)
	{
		STRATEGIX_WARNING(e.what());
		return nullptr;
	}
}

void ParseTechTrees(TechTreesType* pTechTrees)
{
	try
	{
		fs::recursive_directory_iterator it(Kernel::Get("races_config_dir")), eod;
		for (; it != eod; ++it)
		{
			if (fs::is_regular_file(*it) && fs::extension(*it) == ".xml")
			{
				pt::ptree propTree;
				const fs::path& path = it->path();
				try
				{
					pt::read_xml(path.string(), propTree);
					auto&& raceName = path.stem().string();
					auto&& techTree = ParseRace(raceName, propTree.get_child("race"));
					pTechTrees->insert(std::make_pair(raceName, move(techTree)));
				}
				catch (const pt::ptree_error& e)
				{
					STRATEGIX_ERROR(e.what());
				}
			}
		}
	}
	catch (exception& e)
	{
		STRATEGIX_ERROR(e.what());
	}
}

}
