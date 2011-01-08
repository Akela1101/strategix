/* 
 * File:   MyMouseListener.cpp
 * Author: Akela1101
 * 
 * Created on 15 Апрель 2010 г., 16:51
 */

#include "MyMouseListener.h"
#include "MovingManager.h"


namespace Sample1
{
	using namespace Ogre;


MyMouseListener::MyMouseListener(Camera* camera, RaySceneQuery *raySceneQuery)
{
	this->camera = camera;
	this->raySceneQuery = raySceneQuery;
	camera_speed = 0.4f;
	camera_zoom_speed = 0.05f;
	p_currEntity = 0;

//  ### for CEGUI 7.1
//	// CEGUI setup
//	CEGUI::OgreRenderer::bootstrapSystem();
//
//	// Mouse
//	CEGUI::SchemeManager::getSingleton().create((CEGUI::utf8*)"TaharezLook.scheme");
//	CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");
//	CEGUI::System::getSingleton().setMouseMoveScaling(4);

	
}

bool MyMouseListener::mouseMoved(const OIS::MouseEvent &mouse_event)
{	
	// Update CEGUI with the mouse motion
	//CEGUI::System::getSingleton().injectMousePosition(mouse_event.state.X.abs, mouse_event.state.Y.abs);

	camera->moveRelative(Vector3(0, 0, -camera_zoom_speed * mouse_event.state.Z.rel));

	if( mouse_event.state.buttonDown(OIS::MB_Right) )
	{
		// We don't want to yaw in strategy.
		//camera->yaw(Degree(-mouse_event.state.X.rel * camera_speed));
		camera->pitch(Degree(-mouse_event.state.Y.rel * camera_speed));
	}

	return true;
}

bool MyMouseListener::mousePressed(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id)
{
	using namespace Ogre;

	if( id == OIS::MB_Left )
	{
		//CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
		int d_x = mouse_event.state.X.abs;
		int d_y = mouse_event.state.Y.abs;

		Ray mouseRay = camera->getCameraToViewportRay(
				d_x / float(mouse_event.state.width),
				d_y / float(mouse_event.state.height));

		if( p_currEntity ) // Move currently selected Entity.
		{
			// Interset camera-mouse ray with plane XZ.
			Plane terrainPlane(Vector3(0, 1, 0), 0); // XZ
			Real dist = mouseRay.intersects(terrainPlane).second;
			Vector3 intersectPoint = mouseRay.getPoint(dist);

			MovingManager *p_entityManager = any_cast<MovingManager*>(p_currEntity->getUserAny());
			//p_entityManager->AddWayTo_Debug(itr->worldFragment->singleIntersection);
			p_entityManager->AddWayTo(intersectPoint);
		}
		else // No selection => Select
		{
			raySceneQuery->setRay(mouseRay);
			raySceneQuery->setSortByDistance(true);
			RaySceneQueryResult &result = raySceneQuery->execute();

			foreach( RaySceneQueryResultEntry entry, result )
			{
				if( entry.movable && entry.movable->getName() == "Robot" ) // by name - bad ((
				{
					p_currEntity = dynamic_cast<Entity*>(entry.movable);
					p_currEntity->getParentSceneNode()->showBoundingBox(true);
					break;
				}
			}
		}
	}
	return true;
}

bool MyMouseListener::mouseReleased(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id)
{
	return true;
}

}