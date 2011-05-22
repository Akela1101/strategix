/* 
 * File:   MyApp.h
 * Author: Akela1101
 *
 * Created on 14 Февраль 2010 г., 0:58
 */

#ifndef _MYAPP_H
#define	_MYAPP_H

#include <OgrePrerequisites.h>
#include <OgreCommon.h>

#include "Nya.hpp"


// Static plugins declaration section
// Note that every entry in here adds an extra header / library dependency
#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
     // dx10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#    if OGRE_USE_D3D11
#      define OGRE_STATIC_Direct3D11
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
#     undef OGRE_STATIC_CgProgramManager
#     undef OGRE_STATIC_GL
#     define OGRE_STATIC_GLES 1
#     ifdef __OBJC__
#       import <UIKit/UIKit.h>
#     endif
#  endif
#  include "OgreStaticPluginLoader.h"
#endif


namespace Strategix
{
	class Kernel;
}

namespace MyGUI
{
	class Gui;
	class OgrePlatform;
}

namespace Sample1
{
	using namespace Ogre;
	using namespace Strategix;

	class MyFrameListener;
	class MediatorFrameListener;

	class MyApp
	{
	protected:
		Root *root;
		sh_p<MyFrameListener> frameListener;
		sh_p<MediatorFrameListener> mediatorFrameListener;
		sh_p<Kernel> kernel;

	#ifdef OGRE_STATIC_LIB
		StaticPluginLoader mStaticPluginLoader;
	#endif

		Camera* camera;		
		RenderWindow* window;
		String ogreConfigPath;

		bool isConfigure;

		sh_p<MyGUI::Gui> myGUI;
		sh_p<MyGUI::OgrePlatform> myGUI_Platform;

	#ifdef USE_RTSHADER_SYSTEM
		RTShader::ShaderGenerator*					mShaderGenerator;			// The Shader generator instance.
		ShaderGeneratorTechniqueResolverListener*	mMaterialMgrListener;		// Material manager listener.
	#endif

	public:
		MyApp(sh_p<Kernel> kernel);
		virtual ~MyApp();
		virtual void go(const bool isConfigure);

	private:
		virtual bool setup();
		virtual void setupResources();
		virtual bool configure();
		virtual void chooseSceneManager();
		virtual void createCamera();
		virtual void createViewports();
		virtual void createResourceListener();
		virtual void loadResources();
		virtual void createScene();
		virtual void destroyScene();		

		void AddTileToTerrainMesh(ManualObject &mo, const Vector2 &coord, const FloatRect &tex_rect, int &offset);
		void CreateStaticTerrain();
		void CreateMyGUI();
	};
}

#endif	/* _MYAPP_H */

