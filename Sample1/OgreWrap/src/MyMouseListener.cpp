/* 
 * File:   MyMouseListener.cpp
 * Author: Akela1101
 * 
 * Created on 15 Апрель 2010 г., 16:51
 */

#include "OObjectUnit.h"

#include "Enti.h"
#include "FeatureMove.h"

#include <Ogre.h>

#include "Nya.hpp"
#include "MyMouseListener.h"

namespace Sample1
{
	using namespace Ogre;

MyMouseListener::MyMouseListener(Camera* camera, RaySceneQuery *raySceneQuery)
	:
	camera(camera),
	raySceneQuery(raySceneQuery),
	camera_speed(0.4f),
	camera_zoom_speed(0.01f),
	currEntity(0),
	lastEntity(0),
	currMask(NON_MASK)
{
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

	if( mouse_event.state.buttonDown(OIS::MB_Middle) )
	{
		// We don't want to yaw in strategy.
		// comment next line later !!
		camera->yaw(Degree(-mouse_event.state.X.rel * camera_speed));

		camera->pitch(Degree(-mouse_event.state.Y.rel * camera_speed));
	}

	return true;
}

bool MyMouseListener::mousePressed(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id)
{
	if( id == OIS::MB_Left ) // Selection
	{
		//CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();

		// Try to select one object
		Ray mouseRay = GetMouseRay(mouse_event);
		raySceneQuery->setRay(mouseRay);
		raySceneQuery->setSortByDistance(true);
		RaySceneQueryResult &result = raySceneQuery->execute();

		currEntity = 0;
		foreach( RaySceneQueryResultEntry entry, result )
		{
			// If movable and from OObjectUnit
			if( entry.movable && entry.movable->getQueryFlags() & MOV_MASK )
			{
				// Select the nearest
				currEntity = dynamic_cast<Entity*>(entry.movable);
				currEntity->getParentSceneNode()->showBoundingBox(true);
				currMask = MOV_MASK;
				break;
			}
		}

		if( lastEntity != currEntity )
		{
			// Deselect
			if( lastEntity )
			{
				lastEntity->getParentSceneNode()->showBoundingBox(false);
			}
			lastEntity = currEntity;
		}
	}
	else if( id == OIS::MB_Right )  // Move currently selected Entity.
	{
		if( currEntity && currMask & MOV_MASK)
		{
			// Interset camera-mouse ray with plane XZ.
			Plane terrainPlane(Vector3(0, 1, 0), 0); // XZ

			Ray mouseRay = GetMouseRay(mouse_event);
			Real dist = mouseRay.intersects(terrainPlane).second;
			Vector3 intersectPoint = mouseRay.getPoint(dist);

			OObjectUnit *oObjectUnit = any_cast<OObjectUnit*>(currEntity->getUserAny());
			oObjectUnit->enti->Move()(RealCoord(intersectPoint.x, intersectPoint.z));
		}
	}

	return true;
}

bool MyMouseListener::mouseReleased(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id)
{
	return true;
}

Ray MyMouseListener::GetMouseRay(const OIS::MouseEvent &mouse_event) const
{
	const int d_x = mouse_event.state.X.abs;
	const int d_y = mouse_event.state.Y.abs;

	return camera->getCameraToViewportRay(
			(float)d_x / mouse_event.state.width,
			(float)d_y / mouse_event.state.height);
}

}