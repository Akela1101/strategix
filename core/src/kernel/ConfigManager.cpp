#include <entity/EntiInfo.h>
#include <common/TechTree.h>

#include <boost/range/adaptors.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>

#include "ConfigManager.h"


namespace strategix
{
using namespace boost::adaptors;
namespace pt = boost::property_tree;
namespace fs = boost::filesystem;


struct ConfigManager::ConfigurationManagerImpl
{
	string configFile;
	ResourceInfosType resourceInfos;
	TechTreesType techTrees;
	
	u_p<TechTree> ParseRace(const pt::ptree& raceTree)
	{
		try
		{
			auto&& raceName = raceTree.get<string>("name");
			u_p<TechTree> techTree(new TechTree(raceName));
			
			for (auto&& entiTree : raceTree.get_child("entities") | map_values)
			{
				techTree->AddNode(ParseEntity(entiTree));
			}
			return techTree;
		}
		catch (pt::ptree_error& e)
		{
			info_log << e.what();
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
			info_log << e.what();
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
			info_log << "Unable to parse feature: %s. Error: %s"s % name % e.what();
			return nullptr;
		}
	}
	
	u_p<Resources> ParseResources(const pt::ptree& resourcesPropTree)
	{
		try
		{
			auto resources = make_u<Resources>();
			for (auto&& name_tree : resourcesPropTree)
			{
				const string& resourceName = name_tree.first; // gold or something else
				if (find(all_(resourceInfos), resourceName) == resourceInfos.end())
				{
					info_log << "Wrong resource [%s] in configuration file: %s"s
							% resourceName % configFile;
					continue;
				}
				
				const pt::ptree& resource = name_tree.second;
				resources->emplace(resourceName, resource.get_value<ResourceUnit>());
			}
			return resources;
		}
		catch (pt::ptree_error& e)
		{
			info_log << e.what();
			return nullptr;
		}
	}
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ConfigManager::ConfigManager() = default;
ConfigManager::~ConfigManager() = default;

pair<ResourceInfosType, TechTreesType> ConfigManager::ParseConfig(string configFile)
{
	impl.reset(new ConfigurationManagerImpl);
	impl->configFile = configFile;
	try
	{
		pt::ptree propTree;
		pt::read_json(configFile, propTree);
		
		for (auto&& tree : propTree.get_child("resource_types") | map_values)
		{
			const string& resourceName = tree.get_value<string>();
			impl->resourceInfos.push_back(resourceName);
		}
		
		for (auto&& tree : propTree.get_child("races") | map_values)
		{
			auto&& techTree = impl->ParseRace(tree);
			auto&& raceName = techTree->GetRaceName();
			impl->techTrees.emplace(raceName, move(techTree));
		}
	}
	catch (const pt::ptree_error& e)
	{
		info_log << e.what();
	}
	catch (exception& e)
	{
		error_log << "Unexpected error: " << e.what();
	}
	return make_p(move(impl->resourceInfos), move(impl->techTrees));
}

}
