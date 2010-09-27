/* 
 * File:   OgreWrapCommon.h
 * Author: Akela1101
 *
 * Created on 5 Апрель 2010 г., 17:31
 */

#ifndef _OGREWRAPCOMMON_H
#define	_OGREWRAPCOMMON_H

namespace Sample1
{
	enum QueryFlags
	{
		TERRAIN_MASK = 1 << 0, // Don't work
		ROBOT_MASK = 1 << 1
	};

	extern const float tile_length; // Lenght of tile's side
}

#endif	/* _OGREWRAPCOMMON_H */

