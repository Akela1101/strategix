/* 
 * File:   MyAppCommon.h
 * Author: Akela1101
 *
 * Created on 5 Апрель 2010 г., 17:31
 */

#ifndef _MYAPPCOMMON_H
#define	_MYAPPCOMMON_H

namespace Ogre
{
	class SceneManager;
}

namespace Sample1
{
	enum QueryFlags
	{
		NON_MASK = 0, // For nothing
		MOV_MASK = 1 << 0  // For created inside moving manager
	};

	class Mediator;
	extern Mediator *mediator;

	extern Ogre::SceneManager *sceneManager;

	extern const float tile_length; // Lenght of tile's side
}

#endif	/* _MYAPPCOMMON_H */

