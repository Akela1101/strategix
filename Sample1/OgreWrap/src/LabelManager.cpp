/* 
 * File:   LabelManager.cpp
 * Author: Akela1101
 * 
 * Created on 23 Апрель 2010 г., 11:49
 */


#include "MyAppCommon.h"
#include "ObjectTitle.h"

#include "OgreSceneManager.h"

#include "Exception.h"

#include <sstream>

#include "LabelManager.h"


namespace Sample1
{
	using namespace Ogre;
	using namespace std;

LabelManager::LabelManager(const Strategix::MapCoord &mapCoord, const String &title)
	:
	EntityManager("", mapCoord)
{
	this->mapCoord = mapCoord;

	// Creating point mesh for all.
	static bool isNoMesh = true;
	if( isNoMesh )
	{
		ManualObject mo("TilePoint");
		mo.begin("BaseWhiteNoLighting", RenderOperation::OT_POINT_LIST);
		mo.position(0, 0, 0);
		mo.end();
		mo.convertToMesh("PointMesh");

		isNoMesh = false;
	}

	entity = sceneManager->createEntity("PointMesh");
	node = sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(entity);
	node->setPosition(Vector3((mapCoord.x + 0.5f) * tile_length, tile_length, (mapCoord.y + 0.5f) * tile_length));
	node->setVisible(false);

	// Title
	Camera* camera = sceneManager->getCamera("Camera");
	if( !camera )
		STRATEGIX_ERROR("No camera named Camera");

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

void LabelManager::Update()
{
	objectTitle->update();
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