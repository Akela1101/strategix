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
		TERRAIN_MASK = 1 << 0, // Don't work
		ROBOT_MASK = 1 << 1
	};

	class MyManager;

	// GLOBALS
	extern const float tile_length; // Lenght of tile's side
	extern Ogre::SceneManager *sceneManager;
	extern MyManager *myManager;
}

#endif	/* _OGREWRAPCOMMON_H */

