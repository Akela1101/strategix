/* 
 * File:   MyMouseListener.h
 * Author: Akela1101
 *
 * Created on 15 Апрель 2010 г., 16:51
 */

#ifndef _MYMOUSELISTENER_H
#define	_MYMOUSELISTENER_H

#include <Ogre.h>
#include <OIS/OIS.h>

namespace Sample1
{
	using namespace Ogre;

	class MyMouseListener : public OIS::MouseListener
	{
		Camera* camera;
		RaySceneQuery *raySceneQuery;
		float camera_speed, camera_zoom_speed;
		Entity *p_currEntity;

	public:
		MyMouseListener(Camera* camera, RaySceneQuery *raySceneQuery);
		virtual ~MyMouseListener() {}

		bool mouseMoved(const OIS::MouseEvent &mouse_event);
		bool mousePressed(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id);

	};
}

#endif	/* _MYMOUSELISTENER_H */

