/* 
 * File:   MyFrameListener.cpp
 * Author: Akela1101
 * 
 * Created on 5 Апрель 2010 г., 15:32
 */

#include "MyFrameListener.h"
#include "OgreWrapCommon.h"
#include "Kernel.h"

#include <CEGUI/CEGUISystem.h>

namespace Sample1
{
	using namespace Ogre;

MyFrameListener::MyFrameListener(RenderWindow* mWindow, Camera* mCamera)
	:
	ExampleFrameListener(mWindow, mCamera, false, true),
	raySceneQuery(sceneManager->createRayQuery(Ray())),
	mouseListener(new MyMouseListener(mCamera, raySceneQuery))
{	
	mMouse->setEventCallback(mouseListener.get());

	CreateLabels();
	ShowLabels(false);
}

MyFrameListener::~MyFrameListener()
{
	sceneManager->destroyQuery(raySceneQuery);
}

bool MyFrameListener::frameStarted(const FrameEvent &event)
{
	if( !ExampleFrameListener::frameStarted(event) )
		return false;

	Vector3 camPos = mCamera->getPosition();

	// Set mCamera positon over the terrain
	static Vector3 lastCamPos;
	if( lastCamPos != camPos )
	{
		using Strategix::Game;

		float w = Game::GS().GetMap().GetWidth() * tile_length;
		float l = Game::GS().GetMap().GetLength() * tile_length;

		if( camPos.y < tile_length )
			camPos.y = tile_length;

//		if( camPos.x < 0 )
//			camPos.x = 0;
//		if( camPos.x > w )
//			camPos.x = w;
//
//		if( camPos.z < 0 )
//			camPos.z = 0;
//		if( camPos.z > l )
//			camPos.z = l;

		mCamera->setPosition(camPos);
		lastCamPos = camPos;
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
		ShowLabels(!isShowLabels);

		mTimeUntilNextToggle = 0.2;
	}

	// Return true to continue rendering
	return true;
}

#include "LabelManager.h"
#include <vector>
#include <Nya.hpp>
#include <sstream>

void MyFrameListener::CreateLabels()
{
	const Strategix::Map &map = Strategix::Game::GS().GetMap();
	const int width = map.GetWidth();
	const int length = map.GetLength();

	labelVector.reserve(width * length);

	for( int x = 0; x < width; ++x )
	{
		for( int z = 0; z < length; ++z )
		{
			std::stringstream title;
			title << "   " << map(x, z).retard;
			sh_p<LabelManager> labelManager(new LabelManager(Strategix::MapCoord(x, z), title.str().c_str()));

			labelManager->SetColor(ColourValue(1.0, 0.4, 0.4, 1.0));

			labelVector.push_back(labelManager);
		}
	}
}

void MyFrameListener::ShowLabels(bool isShow)
{
	isShowLabels = isShow;

	for( LabelVector::iterator it = labelVector.begin(); it != labelVector.end(); ++it )
	{
		(*it)->Show(isShow);
	}
}

}
