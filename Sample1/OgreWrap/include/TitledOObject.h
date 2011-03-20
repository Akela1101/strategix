/* 
 * File:   TitledOObject.h
 * Author: Akela1101
 *
 * Created on 18 Март 2011 г., 19:03
 */

#ifndef _TITLEDOOBJECT_H
#define	_TITLEDOOBJECT_H

#include "OObject.h"
//______
#include "ObjectTitle.h"

#include <OgrePrerequisites.h>

#include "Nya.hpp"


namespace Sample1
{
	using namespace Ogre;

	//class ObjectTitle;

	class TitledOObject : public OObject
	{
	public:
		sh_p<ObjectTitle> objectTitle;

	public:
		TitledOObject(const std::string &meshName, const std::string &title);
		virtual ~TitledOObject();
	};
}

#endif	/* _TITLEDOOBJECT_H */

