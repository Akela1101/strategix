/* 
 * File:   ConfigurationBuilder.h
 * Author: Akela1101
 *
 * Created on 28 Июнь 2011 г., 20:23
 */

#ifndef _CONFIGURATIONBUILDER_H
#define	_CONFIGURATIONBUILDER_H

#include "ResourceInfo.h"


namespace Strategix
{
	class ConfigurationBuilder
	{
	public:
		virtual ~ConfigurationBuilder() {};

		virtual void Build(ResourceInfosType *pResourceInfos) = 0;
	};
}

#endif	/* _CONFIGURATIONBUILDER_H */

