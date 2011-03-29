/* 
 * File:   OObjectTitled.h
 * Author: Akela1101
 *
 * Created on 18 Март 2011 г., 19:03
 */

#ifndef _OOBJECTTITLED_H
#define	_OOBJECTTITLED_H

#include "OObject.h"
//______
#include "ObjectTitle.h"

#include <OgrePrerequisites.h>

#include "Nya.hpp"


namespace Sample1
{
	using namespace Ogre;

	//class ObjectTitle;

	class OObjectTitled : public OObject
	{
	public:
		sh_p<ObjectTitle> objectTitle;

	public:
		OObjectTitled(const std::string &meshName, const std::string &title);
		virtual ~OObjectTitled();
	};
}

#endif	/* _OOBJECTTITLED_H */

