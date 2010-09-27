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
#include "LabelManager.h"

#include <string>

namespace Sample1
{
	//using namespace Strategix;
	using namespace Ogre;

// GLOBAL
const float tile_length = 10.0f; // Lenght of tile's side

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
	
	MapTexture map_texture("terrains.def");
	
	ManualObject mo("TerrainObject");
	const int width = Map::GS().GetWidth();
	const int length = Map::GS().GetLength();

	mo.begin(map_texture.name, RenderOperation::OT_TRIANGLE_LIST);

	int offset = 0;
	for( int z = 0; z < length; ++z )
	{
		for( int x = 0; x < width; ++x )
		{
			// Getting terrain type (x, z)
			short terrType = Map::GS()(x, z).terrType;
			// Getting it's name
			const string &tex_name = Map::GS().GetTerrain(terrType).name;
			// Getting picture's part rectangle
			const FloatRect rc = map_texture.GetTexRect(tex_name);
			// Adding to (x, z) square with this texture
			AddTileToTerrainMesh(mo, Vector2(x, z), rc, offset);
		}
	}

	mo.end();
	mo.convertToMesh("TerrainMesh");

	//
	Entity *terrain_ent = mSceneMgr->createEntity("terrain", "TerrainMesh");
	//terrain_ent->setQueryFlags(TERRAIN_MASK); // Don't work
	
	StaticGeometry *sg = mSceneMgr->createStaticGeometry("TerrainArea");

	const float map_width = width * tile_length;
	const float map_length = length * tile_length;
	const float map_max_hight = tile_length * 10; // so about

	sg->setRegionDimensions(Vector3(map_width, map_max_hight, map_length));
	sg->setOrigin(Vector3(0, 0, 0));

	sg->addEntity(terrain_ent, Vector3(0, tile_length / 512, 0)); // a bit higher, (kind of magic ^_^)

	sg->build();

	//
	mCamera->setPosition(map_width / 2, map_width / 1.5, map_length);
	mCamera->lookAt(map_width / 2, 0, map_length / 1.5);
}

//==============================================================================
void OgreWrap::chooseSceneManager()
{
	// Use the terrain scene manager.
	mSceneMgr = mRoot->createSceneManager(ST_EXTERIOR_CLOSE);
}

//==============================================================================
void OgreWrap::createScene()
{
	mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	// Using for getting ray results,
	// while i don't know how create world fragment from mesh.
	// And i noticed, ray don't work if is not above terrain !
	mSceneMgr->setWorldGeometry("terrain.cfg");

	//	
	CreateStaticTerrain();

	MovingManager *p_entity_manager = new MovingManager("Robot", mSceneMgr, Strategix::MapCoord(4, 4));
}

//==============================================================================
void OgreWrap::createFrameListener()
{
	mFrameListener = new MyFrameListener(mWindow, mCamera, mSceneMgr);
	mFrameListener->showDebugOverlay(true);
	mRoot->addFrameListener(mFrameListener);
}

//==============================================================================

}
