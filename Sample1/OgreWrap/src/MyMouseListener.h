/* 
 * File:   MyMouseListener.h
 * Author: Akela1101
 *
 * Created on 15 Апрель 2010 г., 16:51
 */

#ifndef _MYMOUSELISTENER_H
#define	_MYMOUSELISTENER_H

#include <Ogre.h>
#include <OIS.h>

#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace Ogre;

	class MyMouseListener : public OIS::MouseListener
	{
		Camera* camera;
		RaySceneQuery *raySceneQuery;
		float camera_speed, camera_zoom_speed;
		Entity *currEntity, *lastEntity;
		QueryFlags currMask;

	public:
		MyMouseListener(Camera* camera);
		virtual ~MyMouseListener();

		bool mouseMoved(const OIS::MouseEvent &mouse_event);
		bool mousePressed(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id);

	private:
		Ray GetMouseRay(const OIS::MouseEvent &mouse_event) const;
		const Vector3 GetTerrainCoord(const OIS::MouseEvent &mouse_event) const;
		Entity *SelectEntity(const OIS::MouseEvent &mouse_event, QueryFlags &newMask) const;
	};
}

#endif	/* _MYMOUSELISTENER_H */

