#ifndef _CONFIGURATIONBUILDER_H
#define    _CONFIGURATIONBUILDER_H

#include <utility>
#include <string>

#include <common/Strategix_Forward.h>

namespace strategix
{

/// Reusable configuration manager.
class ConfigManager
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

#endif    /* _CONFIGURATIONBUILDER_H */

