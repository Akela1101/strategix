#pragma once

#include <utility>
#include <string>

#include <Strategix_fwd.h>

namespace strx
{

/// Reusable configuration manager.
class ConfigManager : boost::noncopyable
{
	struct ConfigurationManagerImpl;
	u_p<ConfigurationManagerImpl> impl;
	
public:
	ConfigManager();
	~ConfigManager();
	/**
	 * @param configFile path of configuration file .json
	 * @return valid resource names and technology trees
	 */
	pair<ResourceInfosType, TechTreesType> ParseConfig(string configFile);
};

}
