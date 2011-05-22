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
		NO_MASK = 0, // For nothing
		UNIT_MASK = 1 << 0,  // Units
		RES_MASK = 2 << 1, // Resources
	};

	extern Ogre::SceneManager *sceneManager;
}

#endif	/* _MYAPPCOMMON_H */

