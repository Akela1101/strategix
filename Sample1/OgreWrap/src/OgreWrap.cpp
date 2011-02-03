/* 
 * File:   OgreWrap.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 0:58
 */

#include "OgreWrap.h"
#include "OgreWrapCommon.h"
#include "MyFrameListener.h"
#include "Map.h"
#include "MapTexture.h"
#include "MovingManager.h"

#include <string>

namespace Sample1
{
	//using namespace Strategix;
	using namespace Ogre;

	// GLOBALS
	const float tile_length = 10.0f; // Lenght of tile's side
	SceneManager *sceneManager;
	MyManager *myManager;


OgreWrap::OgreWrap() : ExampleApplication()
{
	mResourcePath = "OgreWrap/";
    mConfigPath = mResourcePath;
}

//==============================================================================
// Adding tile to map in tile's coordinates coord{x,y}
// with part of texture given from rectangle.
// Also it shifts offset of point number.
void OgreWrap::AddTileToTerrainMesh(ManualObject &mo, const Vector2 &coord, const FloatRect &tex_rect, int &offset)
{
	mo.position(coord.x * tile_length, 0, (coord.y + 1) * tile_length);
	mo.textureCoord(tex_rect.left, tex_rect.top);

	mo.position((coord.x + 1) * tile_length, 0, (coord.y + 1) * tile_length);
	mo.textureCoord(tex_rect.right, tex_rect.top);

	mo.position(coord.x * tile_length, 0, coord.y * tile_length);
	mo.textureCoord(tex_rect.left, tex_rect.bottom);

	mo.position((coord.x + 1) * tile_length, 0, coord.y * tile_length);
	mo.textureCoord(tex_rect.right, tex_rect.bottom);

	// Clockwise culling
	//mo.triangle(offset, offset + 1, offset + 2);
	//mo.triangle(offset + 3, offset + 2, offset + 1);
	mo.quad(offset, offset + 1, offset + 3, offset + 2);

	offset += 4;
}

//==============================================================================
void OgreWrap::CreateStaticTerrain()
{
	using Strategix::Map;
	const Map &gameMap = Strategix::Game::GS().GetMap();

	MapTexture map_texture("Maps/terrains.def"); // WTF ?

	// @#~ Must be done with drawing on texture of one Rectangular mesh!!!
	ManualObject mo("TerrainObject");
	const int width = gameMap.GetWidth();
	const int length = gameMap.GetLength();

	mo.begin(map_texture.name, RenderOperation::OT_TRIANGLE_LIST);

	int offset = 0;
	for( int z = 0; z < length; ++z )
	{
		for( int x = 0; x < width; ++x )
		{
			// Getting terrain type (x, z)
			short terrType = gameMap(x, z).terrType;
			// Getting it's name
			const string &tex_name = Map::GetTerrain(terrType).name;
			// Getting picture's part rectangle
			const FloatRect rc = map_texture.GetTexRect(tex_name);
			// Adding to (x, z) square with this texture
			AddTileToTerrainMesh(mo, Vector2(x, z), rc, offset);
		}
	}
	mo.end();
	mo.convertToMesh("TerrainMesh");
	Entity *terrainEntity = mSceneMgr->createEntity("terrain", "TerrainMesh");
	
	StaticGeometry *sg = mSceneMgr->createStaticGeometry("TerrainArea");

	const float map_width = width * tile_length;
	const float map_length = length * tile_length;
	const float map_max_hight = tile_length * 10; // so about

	sg->setRegionDimensions(Vector3(map_width, map_max_hight, map_length));
	sg->setOrigin(Vector3(0, 0, 0));

	sg->addEntity(terrainEntity, Vector3(0, 0, 0)); // From 0,0 to ZX ↓→

	sg->build();

	// Camera !!
	mCamera->setPosition(map_width / 1.7, map_width / 4, map_length * 1.2);
	mCamera->lookAt(map_width / 2, 0, 0);
}

//==============================================================================
void OgreWrap::chooseSceneManager()
{
	// ST_EXTERIOR_CLOSE was when terrain used.
	mSceneMgr = mRoot->createSceneManager(ST_GENERIC);
	sceneManager = mSceneMgr; // Make it global
}

//==============================================================================
void OgreWrap::createScene()
{	
	mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	MovableObject::setDefaultQueryFlags(0); // very important to precise this string before any Entity definition.

	CreateStaticTerrain();

	using namespace Strategix;

	// Install initial objects on map
	myManager = new MyManager();
	
	foreach( sh_p<Player> &p, Game::GS().players )
	{
		// Getting Base's name.
		const string *baseName = 0;
		foreach( const TechMapPairType &entPair, p->techTree->techMap )
		{
			if( entPair.second->kind == "building_base" )
			{
				baseName = &entPair.second->name;
				break;
			}
		}
		if( !baseName )
		{
			throw STRATEGIX_ERROR("There is no defined entity with kind=building_base");
		}

		// Getting Initial Position
		MapCoord &mapCoord = Game::GS().GetMap().initialPositions[p->playerNumber];

		// Creating Base
		sh_p<MovingManager> base(new MovingManager(p.get(), *baseName, mapCoord));
		myManager->AddEntityManager(base);
	}	 
}

//==============================================================================
void OgreWrap::destroyScene()
{
	delete myManager;
}

//==============================================================================
void OgreWrap::createFrameListener()
{
	mFrameListener = new MyFrameListener(mWindow, mCamera);
	mFrameListener->showDebugOverlay(true);
	mRoot->addFrameListener(mFrameListener);
}

//==============================================================================

}
