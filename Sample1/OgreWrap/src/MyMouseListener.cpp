/* 
 * File:   MyMouseListener.cpp
 * Author: Akela1101
 * 
 * Created on 15 Апрель 2010 г., 16:51
 */

#include "MyMouseListener.h"

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

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

	// CEGUI setup
	CEGUI::OgreRenderer::bootstrapSystem();

	// Mouse
	CEGUI::SchemeManager::getSingleton().create((CEGUI::utf8*)"TaharezLook.scheme");
	CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");
	CEGUI::System::getSingleton().setMouseMoveScaling(4);
}

bool MyMouseListener::mouseMoved(const OIS::MouseEvent &mouse_event)
{
	// Update CEGUI with the mouse motion
	//CEGUI::System::getSingleton().injectMouseMove(mouse_event.state.X.rel, mouse_event.state.Y.rel);

	CEGUI::System::getSingleton().injectMousePosition(mouse_event.state.X.abs, mouse_event.state.Y.abs);

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
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
		Ray mouseRay = camera->getCameraToViewportRay(
				mousePos.d_x / float(mouse_event.state.width),
				mousePos.d_y / float(mouse_event.state.height));
		raySceneQuery->setRay(mouseRay);
		//raySceneQuery->setSortByDistance(true);
		//raySceneQuery->setQueryMask(~TERRAIN_MASK); // don't work

		RaySceneQueryResult &result = raySceneQuery->execute();
		RaySceneQueryResult::iterator itr = result.begin();

		for( ; itr != result.end(); ++itr )
		{
			// No selection => Select
			if( !p_currEntity && itr->movable && itr->movable->getName() == "Robot" ) // by name - bad ((
			{
				p_currEntity = dynamic_cast<Entity*>(itr->movable);
				p_currEntity->getParentSceneNode()->showBoundingBox(true);
				break;
			}
			// There is selection => Move it
			else if( p_currEntity && itr->worldFragment ) // Try to do it with mesh not a world
			{
				MovingManager *p_entityManager = any_cast<MovingManager*>(p_currEntity->getUserAny());

				// _Debug : First time - show, then go
				//p_entityManager->AddWayTo_Debug(itr->worldFragment->singleIntersection);
				p_entityManager->AddWayTo(itr->worldFragment->singleIntersection);
				break;
			}
		}

	}
	else if( id == OIS::MB_Right )
	{
		CEGUI::MouseCursor::getSingleton().hide();
	}
	return true;
}

bool MyMouseListener::mouseReleased(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id)
{
	if( id == OIS::MB_Right )
	{
		CEGUI::MouseCursor::getSingleton().show();
	}
	return true;
}

}