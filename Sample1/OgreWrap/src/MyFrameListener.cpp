/* 
 * File:   MyFrameListener.cpp
 * Author: Akela1101
 * 
 * Created on 5 Апрель 2010 г., 15:32
 */

#include "MyMouseListener.h"
#include "LabelsHolder.h"
#include "MyAppCommon.h"

#include "OgreStringConverter.h"

#include <sstream>

#include "MyFrameListener.h"


namespace Sample1
{
	using namespace Ogre;

MyFrameListener::MyFrameListener(RenderWindow* mWindow, Camera* mCamera)
	:
	mWindow(mWindow),
	mCamera(mCamera),
	mTranslateVector(Vector3::ZERO),
	mCurrentSpeed(0),
	mStatsOn(true),
	mNumScreenShots(0),
	mMoveScale(0.0f),
	mRotScale(0.0f),
	mTimeUntilNextToggle(0),
	mFiltering(TFO_BILINEAR),
	mAniso(1),
	mSceneDetailIndex(0),
	mMoveSpeed(100),
	mRotateSpeed(36),
	mDebugOverlay(OverlayManager::getSingleton().getByName("Core/DebugOverlay")),
	raySceneQuery(sceneManager->createRayQuery(Ray())),
	mouseListener(new MyMouseListener(mCamera, raySceneQuery)),
	labelsHolder(new LabelsHolder())
{
	LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	//pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	//pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	//pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	//pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

	mInputManager = OIS::InputManager::createInputSystem(pl);

	//Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
	try
	{
		mJoy = static_cast<OIS::JoyStick*>(mInputManager->createInputObject(OIS::OISJoyStick, false)); // false ?
	}
	catch( ... )
	{
		mJoy = 0;
	}

	//Set initial mouse clipping size
	windowResized(mWindow);

	showDebugOverlay(true);

	//Register as a Window listener
	WindowEventUtilities::addWindowEventListener(mWindow, this);

	mMouse->setEventCallback(mouseListener.get());

//	Root::getSingleton().addFrameListener(labelsHolder.get());
//
//	labelsHolder->CreateLabels();
//	labelsHolder->ShowLabels(false);
}

MyFrameListener::~MyFrameListener()
{
	//Remove ourself as a Window listener
	WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	sceneManager->destroyQuery(raySceneQuery);
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

	if( mKeyboard->isKeyDown(OIS::KC_W) || mKeyboard->isKeyDown(OIS::KC_UP) )
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
		static bool isShowLabels;
		labelsHolder->ShowLabels(!isShowLabels);

		mTimeUntilNextToggle = 0.2;
	}

	// Return true to continue rendering
	return true;
}

bool MyFrameListener::frameStarted(const FrameEvent &event)
{
	Vector3 camPos = mCamera->getPosition();

	// Set mCamera positon over the terrain
	static Vector3 lastCamPos;
	if( lastCamPos != camPos )
	{
		if( camPos.y < tile_length )
			camPos.y = tile_length;

		mCamera->setPosition(camPos);
		lastCamPos = camPos;
	}

	return true;
}

bool MyFrameListener::frameRenderingQueued(const FrameEvent& evt)
{

	if( mWindow->isClosed() ) return false;

	mSpeedLimit = mMoveScale * evt.timeSinceLastFrame;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();
	if( mJoy ) mJoy->capture();

	bool buffJ = (mJoy) ? mJoy->buffered() : true;

	Ogre::Vector3 lastMotion = mTranslateVector;

	//Check if one of the devices is not buffered
	if( !mMouse->buffered() || !mKeyboard->buffered() || !buffJ )
	{
		// one of the input modes is immediate, so setup what is needed for immediate movement
		if( mTimeUntilNextToggle >= 0 )
			mTimeUntilNextToggle -= evt.timeSinceLastFrame;

		// Move about 100 units per second
		mMoveScale = mMoveSpeed * evt.timeSinceLastFrame;
		// Take about 10 seconds for full rotation
		mRotScale = mRotateSpeed * evt.timeSinceLastFrame;

		mRotX = 0;
		mRotY = 0;
		mTranslateVector = Ogre::Vector3::ZERO;

	}

	if( !mKeyboard->buffered() )
		if( processUnbufferedKeyInput(evt) == false )
			return false;

	// ramp up / ramp down speed
	if( mTranslateVector == Ogre::Vector3::ZERO )
	{
		// decay (one third speed)
		mCurrentSpeed -= evt.timeSinceLastFrame * 0.3;
		mTranslateVector = lastMotion;
	}
	else
	{
		// ramp up
		mCurrentSpeed += evt.timeSinceLastFrame;

	}
	// Limit motion speed
	if( mCurrentSpeed > 1.0 )
		mCurrentSpeed = 1.0;
	if( mCurrentSpeed < 0.0 )
		mCurrentSpeed = 0.0;

	mTranslateVector *= mCurrentSpeed;


	if( !mMouse->buffered() || !mKeyboard->buffered() || !buffJ )
		moveCamera();

	return true;
}

bool MyFrameListener::frameEnded(const FrameEvent& evt)
{
	updateStats();
	return true;
}

void MyFrameListener::updateStats()
{
	static String currFps = "Current FPS: ";
	static String avgFps = "Average FPS: ";
	static String bestFps = "Best FPS: ";
	static String worstFps = "Worst FPS: ";
	static String tris = "Triangle Count: ";
	static String batches = "Batch Count: ";

	// update stats when necessary
	try
	{
		OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
		OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
		OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
		OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

		const RenderTarget::FrameStats& stats = mWindow->getStatistics();
		guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
		guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
		guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS)
				+ " " + StringConverter::toString(stats.bestFrameTime) + " ms");
		guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)
				+ " " + StringConverter::toString(stats.worstFrameTime) + " ms");

		OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
		guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));

		OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
		guiBatches->setCaption(batches + StringConverter::toString(stats.batchCount));

		OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setCaption(mDebugText);
	}
	catch( ... )
	{
		/* ignore */
	}
}

//Adjust mouse clipping area
void MyFrameListener::windowResized(RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void MyFrameListener::windowClosed(RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if( rw == mWindow )
	{
		if( mInputManager )
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);
			mInputManager->destroyInputObject(mJoy);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

void MyFrameListener::moveCamera()
{
	//mCamera->moveRelative(mTranslateVector);
	mCamera->move(mTranslateVector);
}

void MyFrameListener::showDebugOverlay(bool show)
{
	if( mDebugOverlay )
	{
		if( show )
			mDebugOverlay->show();
		else
			mDebugOverlay->hide();
	}
}

}
