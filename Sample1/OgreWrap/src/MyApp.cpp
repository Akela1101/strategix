/* 
* File:   MyApp.cpp
* Author: Akela1101
* 
* Created on 14 Февраль 2010 г., 0:58
*/

#include "FrameListenerKernelSlot.h"
#include "MyAppCommon.h"
#include "MyFrameListener.h"
#include "OObjectEntiSlot.h"
#include "TerrainPositioner.h"

#include <Strategix.h>
#include <Ogre.h>
#include <string>

#include "MyApp.h"


namespace Sample1
{
	using namespace Ogre;

	// GLOBALS	
	SceneManager *sceneManager; // link to Root::SceneManager	

	
//==============================================================================
MyApp::MyApp(sh_p<Kernel> kernel)
	:
	ogreConfigPath("OgreWrap/"),
	kernel(kernel)
{
#ifdef USE_RTSHADER_SYSTEM
	mShaderGenerator = NULL;
	mMaterialMgrListener = NULL;
#endif
}

MyApp::~MyApp()
{
	destroyScene();
	
	if( root )
		OGRE_DELETE root;

#ifdef OGRE_STATIC_LIB
	mStaticPluginLoader.unload();
#endif
}

void MyApp::go(const bool isConfigure)
{
	this->isConfigure = isConfigure;

	if( !setup() )
		return;

	root->startRendering();
}

bool MyApp::setup()
{
	String pluginsPath, configPath;
	// only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	#ifdef _DEBUG
		pluginsPath = ogreConfigPath + "plugins_Windows_d.cfg";
	#else
		pluginsPath = ogreConfigPath + "plugins_Windows.cfg";
	#endif
	#else
		pluginsPath = ogreConfigPath + "plugins_Linux.cfg";
	#endif
#endif

#ifndef OGRE_STATIC_LIB
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		configPath = ogreConfigPath + "ogre_Windows.cfg";
	#else
		configPath = ogreConfigPath + "ogre_Linux.cfg";
	#endif
#endif

	root = OGRE_NEW Root(pluginsPath, configPath, ogreConfigPath + "Ogre.log");

#ifdef OGRE_STATIC_LIB
	mStaticPluginLoader.load();
#endif

	setupResources();

	if( isConfigure )
	{
		if( !configure() )
			return false;
	}
	else
	{
		root->restoreConfig();
	}

	window = root->initialise(true);

	chooseSceneManager();
	createCamera();
	createViewports();

	// Set default mipmap level (NB some APIs ignore this)
	TextureManager::getSingleton().setDefaultNumMipmaps(5);

	createResourceListener();

	loadResources();

	createScene();

	return true;
}

// Method which will define the source of resources (other than current folder)
void MyApp::setupResources()
{
	// Load resource paths from config file
	ConfigFile cf;
	cf.load(ogreConfigPath + "resources.cfg");

	// Go through all sections & settings in the file
	ConfigFile::SectionIterator seci = cf.getSectionIterator();

	String secName, typeName, archName;
	while( seci.hasMoreElements() )
	{
		secName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap *settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for( i = settings->begin(); i != settings->end(); ++i )
		{
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
}

// Configures the application - returns false if the user chooses to abandon configuration.
bool MyApp::configure()
{
	// Show the configuration dialog and initialise the system
	if( root->showConfigDialog() )
	{
		return true;
	}
	return false;
}

void MyApp::chooseSceneManager()
{
	sceneManager = root->createSceneManager(ST_GENERIC, "MyInstance");
	// ST_EXTERIOR_CLOSE was when terrain used.
}

void MyApp::createCamera()
{
	// Create the camera
	camera = sceneManager->createCamera("Camera");
	camera->setNearClipDistance(0.5);
}

void MyApp::createViewports()
{
	// Create one viewport, entire window
	Viewport* vp = window->addViewport(camera);
	vp->setBackgroundColour(ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}

// Optional override method where you can create resource listeners (e.g. for loading screens)
void MyApp::createResourceListener()
{
}

// Optional override method where you can perform resource group loading
// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
void MyApp::loadResources()
{
	// Initialise, parse scripts etc
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void MyApp::createScene()
{
	// MyGUI_Platform
	myGUI_Platform.reset(new MyGUI::OgrePlatform());
	myGUI_Platform->initialise(window, sceneManager);

	// very important to precise this string before any Entity definition.
	MovableObject::setDefaultQueryFlags(0);

	// Sky
	sceneManager->setAmbientLight(ColourValue(1, 1, 1));
	sceneManager->setSkyBox(true, "SpaceSkyBox");

	// Terrain
	CreateStaticTerrain();

	// Main FrameListener
	frameListener.reset(new MyFrameListener(window, camera));
	frameListener->showDebugOverlay(true);
	root->addFrameListener(frameListener.get());

	// Mediator between Kernel & Ogre
	frameListenerKernelSlot.reset(new FrameListenerKernelSlot(kernel));
	root->addFrameListener(frameListenerKernelSlot.get());

	// Start
	kernel->Start();
}

void MyApp::destroyScene()
{
	// Use reset, not removeFrameListener!!!
	frameListenerKernelSlot.reset();
	frameListener.reset();

	// MyGUI_Platform (last)
	myGUI_Platform->shutdown();
	myGUI_Platform.reset();
}

// Adding tile to map in tile's coordinates coord{x,y}
// with part of texture given from rectangle.
// Also it shifts offset of point number.
void MyApp::AddTileToTerrainMesh(ManualObject &mo, const Vector2 &coord, const FloatRect &tex_rect, int &offset)
{
	mo.position(coord.x, 0, coord.y + 1);
	mo.textureCoord(tex_rect.left, tex_rect.top);

	mo.position(coord.x + 1, 0, coord.y + 1);
	mo.textureCoord(tex_rect.right, tex_rect.top);

	mo.position(coord.x , 0, coord.y);
	mo.textureCoord(tex_rect.left, tex_rect.bottom);

	mo.position(coord.x + 1, 0, coord.y);
	mo.textureCoord(tex_rect.right, tex_rect.bottom);

	mo.quad(offset, offset + 1, offset + 3, offset + 2);

	offset += 4;
}

void MyApp::CreateStaticTerrain()
{
	using namespace Strategix;
	
	const MapFull &mapFull = kernel->GetMap();

	TerrainPositioner terrainPositioner("Maps/terrains.def"); // WTF ?

	// @#~ Must be done with drawing on texture of one Rectangular mesh!!!
	ManualObject mo("TerrainObject");
	const int width = mapFull.GetWidth();
	const int length = mapFull.GetLength();

	mo.begin(terrainPositioner.name, RenderOperation::OT_TRIANGLE_LIST);

	int offset = 0;
	for( int z = 0; z < length; ++z )
	{
		for( int x = 0; x < width; ++x )
		{
			// Getting terrain type (x, z)
			int terrainType = mapFull.GetCell(x, z).terrainType;
			// Getting it's name
			const string &tex_name = mapFull.GetTerrain(terrainType).name;
			// Getting picture's part rectangle
			const FloatRect rc = terrainPositioner.GetTexRect(tex_name);
			// Adding to (x, z) square with this texture
			AddTileToTerrainMesh(mo, Vector2(x, z), rc, offset);
		}
	}
	mo.end();
	mo.convertToMesh("TerrainMesh");
	Entity *terrainEntity = sceneManager->createEntity("terrain", "TerrainMesh");

	StaticGeometry *sg = sceneManager->createStaticGeometry("TerrainArea");

	const float realWidth = width;
	const float realLength = length;

	sg->setRegionDimensions(Vector3(width, 10.0, length));
	sg->setOrigin(Vector3(0, 0, 0));

	sg->addEntity(terrainEntity, Vector3(0, 0, 0)); // From 0,0 to ZX ↓→

	sg->build();

	// Camera !!
	camera->setPosition(realWidth * 0.5, realWidth / 4, realLength * 1.2);
	camera->lookAt(realWidth * 0.5, 0, 0);
}

}
