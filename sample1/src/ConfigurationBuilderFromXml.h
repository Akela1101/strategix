#ifndef _CONFIGURATIONBUILDERFROMXML_H
#define    _CONFIGURATIONBUILDERFROMXML_H

#include <ConfigurationBuilder.h>
#include <ResourceInfo.h>


namespace Sample1
{
using namespace Strategix;

class ConfigurationBuilderFromXml : public ConfigurationBuilder
{
public:
	void Build(ResourceInfosType* pResourceInfos);
};
}

#endif    /* _CONFIGURATIONBUILDERFROMXML_H */

