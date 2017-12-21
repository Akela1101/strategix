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
	 * @param configFileName path of configuration file .json
	 * @return valid resource names and technology trees
	 */
	void ParseConfig(string configFileName);
	
	ushort GetServerPort() const;
	const string& GetMapsPath() const;
	const ResourceInfosType& GetResourceInfos() const;
	const TechTreesType& GetTechTrees() const;
};

}
