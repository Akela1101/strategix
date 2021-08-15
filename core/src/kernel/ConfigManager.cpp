#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "../../strx/EntityInfo.hpp"
#include "../../strx/TechTree.hpp"

#include "ConfigManager.hpp"


namespace strx
{
namespace pt = boost::property_tree;
namespace fs = boost::filesystem;


struct ConfigurationManagerImpl
{
	const string configFileName;
	ushort serverPort;
	string mapsPath;
	ResourcesContext resourcesContext = make_s<vector<string>>();
	TechTreesType techTrees;

	ConfigurationManagerImpl(string configFileName) : configFileName(configFileName) {}

	void ParseConfig()
	{
		try
		{
			pt::ptree propTree;
			pt::read_json(configFileName, propTree);

			serverPort = propTree.get<ushort>("server_port");
			mapsPath = propTree.get<string>("maps_path");

			for (auto&& tree : propTree.get_child("resource_types") | nya::map_values)
			{
				const string& resourceName = tree.get_value<string>();
				resourcesContext->push_back(resourceName);
			}

			for (auto&& tree : propTree.get_child("races") | nya::map_values)
			{
				auto&& techTree = ParseRace(tree);
				auto&& raceName = techTree->GetRaceName();
				techTrees.emplace(raceName, move(techTree));
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
	}

	u_p<TechTree> ParseRace(const pt::ptree& raceTree)
	{
		try
		{
			auto&& raceName = raceTree.get<string>("name");
			u_p<TechTree> techTree(new TechTree(raceName));

			for (auto&& entiTree : raceTree.get_child("entities") | nya::map_values)
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

	u_p<EntityInfo> ParseEntity(const pt::ptree& entityPropTree)
	{
		try
		{
			u_p<EntityInfo> eim(new EntityInfo);

			eim->name = entityPropTree.get<string>("name");
			eim->kind = entityPropTree.get<string>("kind");
			eim->resources = ParseResources(entityPropTree.get_child("resources"));

			for (auto&& name_tree : entityPropTree.get_child("features", pt::ptree()))  // Empty if no features
			{
				const string& name = name_tree.first;
				if (auto&& feature = ParseFeature(name, name_tree.second)) eim->featureInfos[name] = move(feature);
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
				return make_u<MoveFeatureInfo>(speed);
			}
			else if (name == "collect")
			{
				auto speed = feature.get<float>("speed");
				auto radius = feature.get<float>("radius");
				u_p<Resources> capacities = ParseResources(feature.get_child("capacities"));
				return make_u<CollectFeatureInfo>(speed, radius, move(capacities));
			}
			else if (name == "health")
			{
				auto hp = feature.get<HpType>("hp");
				auto recovery = feature.get<float>("recovery");
				return make_u<HealthFeatureInfo>(hp, recovery);
			}
			else if (name == "attack")
			{
				auto damage = feature.get<HpType>("damage");
				auto speed = feature.get<float>("speed");
				auto radius = feature.get<float>("radius");
				return make_u<AttackFeatureInfo>(damage, speed, radius);
			}
			else
			{
				error_log << "Unknown feature: %s"s % name;
			}
		}
		catch (pt::ptree_error& e)
		{
			error_log << "Unable to parse feature: %s. Error: %s"s % name % e.what();
		}
		return nullptr;
	}

	u_p<Resources> ParseResources(const pt::ptree& resourcesPropTree)
	{
		try
		{
			auto resources = make_u<Resources>();
			for (auto&& name_tree : resourcesPropTree)
			{
				const string& resourceName = name_tree.first;  // gold or something else
				if (find(nya_all(*resourcesContext), resourceName) == resourcesContext->end())
				{
					info_log << "Wrong resource [%s] in configuration file: %s"s % resourceName % configFileName;
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
u_p<ConfigurationManagerImpl> impl;

void ConfigManager::ParseConfig(string configFileName)
{
	impl.reset(new ConfigurationManagerImpl(configFileName));
	impl->ParseConfig();
}

ushort ConfigManager::GetServerPort()
{
	return impl->serverPort;
}
const string& ConfigManager::GetMapsPath()
{
	return impl->mapsPath;
}
const ResourcesContext& ConfigManager::GetResourcesContext()
{
	return impl->resourcesContext;
}
const TechTreesType& ConfigManager::GetTechTrees()
{
	return impl->techTrees;
}

}  // namespace strx
