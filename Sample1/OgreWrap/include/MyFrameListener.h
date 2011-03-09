/* 
 * File:   MyFrameListener.h
 * Author: Akela1101
 *
 * Created on 5 Апрель 2010 г., 15:32
 */

#ifndef _MYFRAMELISTENER_H
#define	_MYFRAMELISTENER_H

#include "Ogre.h"
//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

#include "Nya.hpp"


namespace Sample1
{
	using namespace Ogre;
	using namespace std;

	class MyMouseListener;
	class LabelManager;

	class MyFrameListener : public FrameListener, public WindowEventListener
	{
	protected:
		RenderWindow* mWindow;
		Camera* mCamera;

		Vector3 mTranslateVector;
		Real mCurrentSpeed;
		bool mStatsOn;

		String mDebugText;

		unsigned int mNumScreenShots;
		float mMoveScale;
		float mSpeedLimit;
		Degree mRotScale;
		// just to stop toggles flipping too fast
		Real mTimeUntilNextToggle;
		Radian mRotX, mRotY;
		TextureFilterOptions mFiltering;
		int mAniso;

		int mSceneDetailIndex;
		Real mMoveSpeed;
		Degree mRotateSpeed;
		Overlay* mDebugOverlay;

		//OIS Input devices
		OIS::InputManager* mInputManager;
		OIS::Mouse* mMouse;
		OIS::Keyboard* mKeyboard;
		OIS::JoyStick* mJoy;

		//
		RaySceneQuery *raySceneQuery;
		sh_p<MyMouseListener> mouseListener;

		typedef std::vector<sh_p<LabelManager> > LabelVector;
		LabelVector labelVector;
		bool isShowLabels;

	public:
		MyFrameListener(RenderWindow* mWindow, Camera* mCamera);
		virtual ~MyFrameListener();

		virtual bool processUnbufferedKeyInput(const FrameEvent& evt);
		virtual bool frameStarted(const FrameEvent &event);
		virtual bool frameRenderingQueued(const FrameEvent &event);
		virtual bool frameEnded(const FrameEvent &event);
		virtual void showDebugOverlay(bool show);

	private:
		virtual void updateStats();
		virtual void windowResized(RenderWindow* rw);
		virtual void windowClosed(RenderWindow* rw);
		virtual void moveCamera();
		
		void CreateLabels();
		void ShowLabels(bool isShow);
	};
}

#endif	/* _MYFRAMELISTENER_H */

