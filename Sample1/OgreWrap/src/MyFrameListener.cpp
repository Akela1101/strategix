/* 
 * File:   MyFrameListener.cpp
 * Author: Akela1101
 * 
 * Created on 5 Апрель 2010 г., 15:32
 */

#include "MyFrameListener.h"

#include "OgreWrapCommon.h"
#include "Kernel.h"


namespace Sample1
{
	using namespace Ogre;

MyFrameListener::MyFrameListener(RenderWindow* mWindow, Camera* mCamera, SceneManager *sceneManager)
: ExampleFrameListener(mWindow, mCamera, false, true)
{
	this->sceneManager = sceneManager;
	raySceneQuery = sceneManager->createRayQuery(Ray());

	// Register this so that we get mouse events.
	p_mouse_listener = new MyMouseListener(mCamera, raySceneQuery);
	mMouse->setEventCallback(p_mouse_listener);

	CreateLabels();
}

MyFrameListener::~MyFrameListener()
{
	delete p_mouse_listener;
	sceneManager->destroyQuery(raySceneQuery);
}

bool MyFrameListener::frameStarted(const FrameEvent &event)
{
	if( !ExampleFrameListener::frameStarted(event) )
		return false;

	// Setup the scene query
	Vector3 camPos = mCamera->getPosition();

	// Set mCamera positon under the terrain
	static Vector3 lastCamPos;
	if( lastCamPos != camPos )
	{
		lastCamPos = camPos;

		Ray cameraRay(Vector3(camPos.x, 5000.0f, camPos.z), Vector3::NEGATIVE_UNIT_Y);
		raySceneQuery->setRay(cameraRay);

		// Perform the scene query
		RaySceneQueryResult &result = raySceneQuery->execute();
		RaySceneQueryResult::iterator itr = result.begin();

		// Get the results, set the mCamera height
		bool is_over_terrain = false;
		for(; itr != result.end(); ++itr )
		{
			if( itr->worldFragment )
			{
				is_over_terrain = true;
				Real terrainHeight = itr->worldFragment->singleIntersection.y;
				if( (terrainHeight + 10.0f) > camPos.y )
					mCamera->setPosition(camPos.x, terrainHeight + 10.0f, camPos.z);
			}
		}

		// Camera must be over the terrain for ray to execute !
		if( !is_over_terrain )
		{
			using Strategix::Map;

			Vector3 camera_pos = mCamera->getPosition();
			if( camera_pos.x < 0 ) camera_pos.x = 0;
			float w = Map::GS().GetWidth() * tile_length;
			if( camera_pos.x > w ) camera_pos.x = w;
			if( camera_pos.z < 0 ) camera_pos.z = 0;
			float l = Map::GS().GetLength() * tile_length;
			if( camera_pos.z > l ) camera_pos.z = l;

			mCamera->setPosition(camera_pos);
		}
	}

	return true;
}

bool MyFrameListener::processUnbufferedKeyInput(const FrameEvent& evt)
{
	Real moveScale = mMoveScale;
	if( mKeyboard->isKeyDown(OIS::KC_LSHIFT) )
		moveScale *= 10;

	if( mKeyboard->isKeyDown(OIS::KC_A) || mKeyboard->isKeyDown(OIS::KC_LEFT) )
		mTranslateVector.x = -moveScale; // Move camera left

	if( mKeyboard->isKeyDown(OIS::KC_D) || mKeyboard->isKeyDown(OIS::KC_RIGHT) )
		mTranslateVector.x = moveScale; // Move camera RIGHT

	if( mKeyboard->isKeyDown(OIS::KC_W) || mKeyboard->isKeyDown(OIS::KC_UP)  )
		mTranslateVector.z = -moveScale; // Move camera forward

	if( mKeyboard->isKeyDown(OIS::KC_S) || mKeyboard->isKeyDown(OIS::KC_DOWN) )
		mTranslateVector.z = moveScale; // Move camera backward

	if( mKeyboard->isKeyDown(OIS::KC_PGUP) )
		mTranslateVector.y = moveScale; // Move camera up

	if( mKeyboard->isKeyDown(OIS::KC_PGDOWN) )
		mTranslateVector.y = -moveScale; // Move camera down


	if( mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q) )
		return false;

	if( mKeyboard->isKeyDown(OIS::KC_F) && mTimeUntilNextToggle <= 0 )
	{
		mStatsOn = !mStatsOn;
		showDebugOverlay(mStatsOn);
		mTimeUntilNextToggle = 1;
	}

	if( mKeyboard->isKeyDown(OIS::KC_T) && mTimeUntilNextToggle <= 0 )
	{
		switch( mFiltering )
		{
			case TFO_BILINEAR:
				mFiltering = TFO_TRILINEAR;
				mAniso = 1;
				break;
			case TFO_TRILINEAR:
				mFiltering = TFO_ANISOTROPIC;
				mAniso = 8;
				break;
			case TFO_ANISOTROPIC:
				mFiltering = TFO_BILINEAR;
				mAniso = 1;
				break;
			default: break;
		}
		MaterialManager::getSingleton().setDefaultTextureFiltering(mFiltering);
		MaterialManager::getSingleton().setDefaultAnisotropy(mAniso);

		showDebugOverlay(mStatsOn);
		mTimeUntilNextToggle = 1;
	}

	if( mKeyboard->isKeyDown(OIS::KC_SYSRQ) && mTimeUntilNextToggle <= 0 )
	{
		StringStream ss;
		ss << "screenshot_" << ++mNumScreenShots << ".png";
		mWindow->writeContentsToFile(ss.str());
		mTimeUntilNextToggle = 0.5;
		mDebugText = "Saved: " + ss.str();
	}

	if( mKeyboard->isKeyDown(OIS::KC_R) && mTimeUntilNextToggle <= 0 )
	{
		mSceneDetailIndex = (mSceneDetailIndex + 1) % 3;
		switch( mSceneDetailIndex )
		{
			case 0: mCamera->setPolygonMode(PM_SOLID);
				break;
			case 1: mCamera->setPolygonMode(PM_WIREFRAME);
				break;
			case 2: mCamera->setPolygonMode(PM_POINTS);
				break;
		}
		mTimeUntilNextToggle = 0.5;
	}

	static bool displayCameraDetails = false;
	if( mKeyboard->isKeyDown(OIS::KC_P) && mTimeUntilNextToggle <= 0 )
	{
		displayCameraDetails = !displayCameraDetails;
		mTimeUntilNextToggle = 0.5;
		if( !displayCameraDetails )
			mDebugText = "";
	}

	// Print camera details
	if( displayCameraDetails )
		mDebugText = "P: " + StringConverter::toString(mCamera->getDerivedPosition()) +
		" " + "O: " + StringConverter::toString(mCamera->getDerivedOrientation());

	// @#~
	if( mKeyboard->isKeyDown(OIS::KC_1) && mTimeUntilNextToggle <= 0 )
	{
		static bool isShow = true;
		isShow = !isShow;
		ShowLabels(isShow);

		mTimeUntilNextToggle = 0.2;
	}

	// Return true to continue rendering
	return true;
}

#include "LabelManager.h"
#include <vector>
#include <boost/smart_ptr.hpp>
#include <sstream>

void MyFrameListener::CreateLabels()
{
	Strategix::Map &r_map = Strategix::Map::GS();
	const int width = r_map.GetWidth();
	const int length = r_map.GetLength();

	labelVector.reserve(width * length);

	for( int x = 0; x < width; ++x )
	{
		for( int z = 0; z < length; ++z )
		{
			std::stringstream title;
			title << "   " << r_map(x, z).retard;
			SHP_LabelManager shp_labelManager(new LabelManager(sceneManager, Strategix::MapCoord(x, z), title.str().c_str()));

			shp_labelManager->SetColor(ColourValue(1.0, 0.4, 0.4, 1.0));

			labelVector.push_back(shp_labelManager);
		}
	}
}

void MyFrameListener::ShowLabels(bool isShow)
{
	for( LabelVector::iterator it = labelVector.begin(); it != labelVector.end(); ++it )
	{
		(*it)->Show(isShow);
	}
}

}
