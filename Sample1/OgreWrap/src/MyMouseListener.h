/* 
 * File:   MyMouseListener.h
 * Author: Akela1101
 *
 * Created on 15 Апрель 2010 г., 16:51
 */

#ifndef _MYMOUSELISTENER_H
#define	_MYMOUSELISTENER_H

#include "MyAppCommon.h"

#include <OgrePrerequisites.h>
#include <OIS.h>


namespace Sample1
{
	using namespace Ogre;

	class MyMouseListener : public OIS::MouseListener
	{
		Camera* camera;		
		float camera_speed, camera_zoom_speed;
		Entity *currEntity, *lastEntity;
		QueryFlags currMask;

		mutable RaySceneQuery *raySceneQuery;

	public:
		MyMouseListener(Camera* camera);
		virtual ~MyMouseListener();

		virtual bool mouseMoved(const OIS::MouseEvent &mouse_event);
		virtual bool mousePressed(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID) { return true; }
		
	private:
		Ray GetMouseRay(const OIS::MouseEvent &mouse_event) const;
		const Vector3 GetTerrainCoord(const OIS::MouseEvent &mouse_event) const;
		Entity *SelectEntity(const OIS::MouseEvent &mouse_event, QueryFlags *newMask = 0) const;

	};
}

#endif	/* _MYMOUSELISTENER_H */

