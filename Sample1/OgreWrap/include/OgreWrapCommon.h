/* 
 * File:   OgreWrapCommon.h
 * Author: Akela1101
 *
 * Created on 5 Апрель 2010 г., 17:31
 */

#ifndef _OGREWRAPCOMMON_H
#define	_OGREWRAPCOMMON_H

#include "OgreSceneManager.h"
#include "MyManager.h"


namespace Sample1
{
	enum QueryFlags
	{
		NON_MASK = 0, // For nothing
		MOV_MASK = 1 << 0  // For created inside moving manager
	};

	class MyManager;

	// GLOBALS
	extern const float tile_length; // Lenght of tile's side
	extern Ogre::SceneManager *sceneManager;
	extern MyManager *myManager;
}

#endif	/* _OGREWRAPCOMMON_H */

