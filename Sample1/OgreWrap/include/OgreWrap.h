/* 
 * File:   OgreWrap.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 0:58
 */

#ifndef _OGREWRAP_H
#define	_OGREWRAP_H

#include "ExampleApplication.h"

namespace Sample1
{
	using namespace Ogre;

	class OgreWrap : public ExampleApplication
	{
		void chooseSceneManager();
		void createScene();
		void createFrameListener();

		void AddTileToTerrainMesh(ManualObject &mo, const Vector2 &coord, const FloatRect &tex_rect, int &offset);
		void CreateStaticTerrain();
	};
}

#endif	/* _OGREWRAP_H */

