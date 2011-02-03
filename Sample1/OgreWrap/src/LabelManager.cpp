/* 
 * File:   LabelManager.cpp
 * Author: Akela1101
 * 
 * Created on 23 Апрель 2010 г., 11:49
 */

#include "LabelManager.h"
#include "OgreWrapCommon.h"
#include "OgreException.h"
#include <sstream>


namespace Sample1
{
	using namespace Ogre;
	using namespace std;

LabelManager::LabelManager(const Strategix::MapCoord &mapCoord, const String &title)
	:
	EntityManager(0, "", mapCoord)
{
	this->mapCoord = mapCoord;

	static bool isNoMesh = true;
	if( isNoMesh )
	{
		ManualObject mo("TilePoint");
		mo.begin("BaseWhiteNoLighting", RenderOperation::OT_POINT_LIST);
		mo.position(0, 0, 0);
		mo.end();
		mo.convertToMesh("TileMesh");

		isNoMesh = false;
	}

	entity = sceneManager->createEntity("TileMesh");
	node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(entity);
	node->setPosition(Vector3((mapCoord.x + 0.5f) * tile_length, tile_length, (mapCoord.y + 0.5f) * tile_length));

	// Title
	Camera* camera = sceneManager->getCamera("Camera");
	if( !camera )
		OGRE_EXCEPT(1, "No camera named Camera", "");

	static int n = 1;
	std::stringstream titleName;
	titleName << "Title" << n++;
	objectTitle = new ObjectTitle(titleName.str().c_str(), entity, camera, title, "Calibri");
}

LabelManager::~LabelManager()
{
	delete objectTitle;
	node->detachObject(entity);
	sceneManager->destroyEntity(entity);
	sceneManager->destroySceneNode(node);
}

bool LabelManager::frameRenderingQueued(const FrameEvent &event)
{
	objectTitle->update();
	return true;
}

void LabelManager::SetColor(const ColourValue& color)
{
	objectTitle->setColor(color);
}

void LabelManager::Show(bool isShow)
{
	objectTitle->show(isShow);
}

}