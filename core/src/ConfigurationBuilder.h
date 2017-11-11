#ifndef _CONFIGURATIONBUILDER_H
#define    _CONFIGURATIONBUILDER_H

#include "ResourceInfo.h"


namespace Strategix
{
class ConfigurationBuilder
{
public:
	virtual ~ConfigurationBuilder() {};
	
	virtual void Build(ResourceInfosType* pResourceInfos) = 0;
};
}

#endif    /* _CONFIGURATIONBUILDER_H */

