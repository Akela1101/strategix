/* 
 * File:   MyFrameListener.h
 * Author: Akela1101
 *
 * Created on 5 Апрель 2010 г., 15:32
 */

#ifndef _MYFRAMELISTENER_H
#define	_MYFRAMELISTENER_H

#include "Nya.hpp"
#include "ExampleFrameListener.h"
#include "MyMouseListener.h"



#include "ObjectTitle.h"
#include "LabelManager.h"

namespace Sample1
{
	using namespace Ogre;
	using namespace std;

	class MyFrameListener : public ExampleFrameListener
	{
		typedef sh_p<LabelManager> SHP_LabelManager;
		typedef std::vector<SHP_LabelManager> LabelVector;
		LabelVector labelVector;

	protected:
		SceneManager *sceneManager; // A pointer to the scene manager
		RaySceneQuery *raySceneQuery; // The ray scene query pointer
		MyMouseListener *p_mouse_listener;

		void CreateLabels();
		void ShowLabels(bool isShow);

	public:
		MyFrameListener(RenderWindow* mWindow, Camera* mCamera, SceneManager *sceneManager);
		~MyFrameListener();
		bool frameStarted(const FrameEvent &event);
		virtual bool processUnbufferedKeyInput(const FrameEvent& evt);
	};
}

#endif	/* _MYFRAMELISTENER_H */

