/* 
 * File:   MyMouseListener.cpp
 * Author: Akela1101
 * 
 * Created on 15 Апрель 2010 г., 16:51
 */

#include "OObjectEntiSlot.h"
#include "OObjectResource.h"

#include <Strategix.h>
#include <Ogre.h>

#include "MyMouseListener.h"


namespace Sample1
{
	using namespace Ogre;

MyMouseListener::MyMouseListener(Camera* camera)
	:
	camera(camera),
	raySceneQuery(sceneManager->createRayQuery(Ray())),
	camera_speed(0.4f),
	camera_zoom_speed(0.01f),
	currEntity(0),
	lastEntity(0),
	currMask(NO_MASK)
{}

MyMouseListener::~MyMouseListener()
{
	sceneManager->destroyQuery(raySceneQuery);
}

bool MyMouseListener::mouseMoved(const OIS::MouseEvent &mouse_event)
{	
	camera->moveRelative(Vector3(0, 0, -camera_zoom_speed * mouse_event.state.Z.rel));

	if( mouse_event.state.buttonDown(OIS::MB_Middle) )
	{
		// @#~ We don't want to yaw in strategy.
		// So comment next line later !!!
		camera->yaw(Degree(-mouse_event.state.X.rel * camera_speed));
		camera->pitch(Degree(-mouse_event.state.Y.rel * camera_speed));
	}
	return true;
}

bool MyMouseListener::mousePressed(const OIS::MouseEvent &mouse_event, OIS::MouseButtonID id)
{
	// Select
	if( id == OIS::MB_Left ) 
	{
		currEntity = SelectEntity(mouse_event, currMask);
		if( currEntity ) // Zero if nothing selected
		{
			currEntity->getParentSceneNode()->showBoundingBox(true);
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
	// Move selected Entity
	else if( id == OIS::MB_Right )  
	{
		if( currEntity && (currMask == ENTI_MASK) )
		{
			OObjectEntiSlot *oObjectEntiSlot = any_cast<OObjectEntiSlot*>(currEntity->getUserAny());
			
			QueryFlags mask;
			Entity *entity = SelectEntity(mouse_event, mask);
			if( entity && (mask == RES_MASK) ) // Collect
			{
				OObjectResource *oObjectResource
					= any_cast<OObjectResource*>(entity->getUserAny());
				oObjectEntiSlot->enti->
					Do<FeatureCollect>()->Collect(oObjectResource->mapResource);
			}
			else if( entity && (mask == ENTI_MASK) ) // Attack
			{
				OObjectEntiSlot *oObjectTarget
					= any_cast<OObjectEntiSlot*>(entity->getUserAny());
				oObjectEntiSlot->enti->Do<FeatureAttack>()->Attack(oObjectTarget->enti);
			}
			else // Move
			{
				const Vector3 &terrainCoord = GetTerrainCoord(mouse_event);
				oObjectEntiSlot->enti->Do<FeatureMove>()->Move(RealCoord(terrainCoord.x, terrainCoord.z));
			}
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
	const float d_x = mouse_event.state.X.abs;
	const float d_y = mouse_event.state.Y.abs;
	const float width = mouse_event.state.width;
	const float height = mouse_event.state.height;

	return camera->getCameraToViewportRay(d_x / width, d_y / height);
}

const Vector3 MyMouseListener::GetTerrainCoord(const OIS::MouseEvent &mouse_event) const
{
	// Interset camera-mouse ray with plane XZ
	static Plane terrainPlane(Vector3(0, 1, 0), 0); // XZ

	Ray mouseRay = GetMouseRay(mouse_event);
	Real dist = mouseRay.intersects(terrainPlane).second;

	return mouseRay.getPoint(dist);
}

Entity *MyMouseListener::SelectEntity(const OIS::MouseEvent &mouse_event, QueryFlags &newMask) const
{
	// Try to select one object
	Ray mouseRay = GetMouseRay(mouse_event);
	raySceneQuery->setRay(mouseRay);
	raySceneQuery->setSortByDistance(true);
	RaySceneQueryResult &result = raySceneQuery->execute();
	
	foreach( RaySceneQueryResultEntry entry, result )
	{
		// If movable and not a terrain
		QueryFlags mask = (QueryFlags)entry.movable->getQueryFlags();
		MovableObject *movable = entry.movable;
		if( movable && mask && currEntity != movable )
		{
			newMask = mask;
			return static_cast<Entity*>(movable);
		}
	}
	return 0;
}

}