#ifndef _CONFIGURATIONBUILDER_H
#define    _CONFIGURATIONBUILDER_H

#include <utility>
#include <string>

#include <Strategix_Forward.h>

namespace strategix
{
using namespace std;

/// Reusable configuration manager.
class ConfigurationManager
{
	struct ConfigurationManagerImpl;
	u_p<ConfigurationManagerImpl> impl;
	
public:
	ConfigurationManager();
	~ConfigurationManager();
	/**
	 * @param configFile path of configuration file .json
	 * @return valid resource names and technology trees
	 */
	pair<ResourceInfosType, TechTreesType> ParseConfig(string configFile);
};

}

#endif    /* _CONFIGURATIONBUILDER_H */

