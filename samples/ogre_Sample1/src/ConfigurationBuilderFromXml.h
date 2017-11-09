/* 
 * File:   ConfigurationBuilderFromXml.h
 * Author: Akela1101
 *
 * Created on 28 Июнь 2011 г., 20:55
 */

#ifndef _CONFIGURATIONBUILDERFROMXML_H
#define	_CONFIGURATIONBUILDERFROMXML_H

#include <ConfigurationBuilder.h>
#include <ResourceInfo.h>


namespace Sample1
{
	using namespace Strategix;
	
	class ConfigurationBuilderFromXml : public ConfigurationBuilder
	{
	public:
		void Build(ResourceInfosType *pResourceInfos);
	};
}

#endif	/* _CONFIGURATIONBUILDERFROMXML_H */

