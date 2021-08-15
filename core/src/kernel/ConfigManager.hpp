#pragma once

#include "../../strx/strx_fwd.hpp"

namespace strx
{
/**
 * Global configuration manager.
 * It should parse config before other actions.
 */
class ConfigManager
{
	ConfigManager() = delete;

public:
	/**
	 * @param configFileName path of configuration file .json
	 * @return valid resource names and technology trees
	 */
	static void ParseConfig(string configFileName);

	static ushort GetServerPort();
	static const string& GetMapsPath();
	static const ResourcesContext& GetResourcesContext();
	static const TechTreesType& GetTechTrees();
};

}  // namespace strx
