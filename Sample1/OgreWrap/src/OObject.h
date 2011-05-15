/* 
 * File:   OObject.h
 * Author: Akela1101
 *
 * Created on 18 Март 2011 г., 15:44
 */

#ifndef _OOBJECT_H
#define	_OOBJECT_H

#include <OgrePrerequisites.h>

#include <string>


namespace Sample1
{
	using namespace Ogre;
	
	class OObject
	{
	protected:
		SceneNode *node;
		Entity *entity;

	public:
		OObject(const std::string &meshName);
		virtual ~OObject();
	};
}

#endif	/* _OOBJECT_H */

