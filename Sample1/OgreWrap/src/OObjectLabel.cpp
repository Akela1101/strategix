/* 
 * File:   OObjectLabel.cpp
 * Author: Akela1101
 * 
 * Created on 23 Апрель 2010 г., 11:49
 */

#include "MyAppCommon.h"

#include <Ogre.h>

#include "OObjectLabel.h"


namespace Sample1
{
	using namespace Ogre;
	using namespace Strategix;

	static const float heightOfLabel = 12.0;


OObjectLabel::OObjectLabel(const std::string &meshName, const std::string &title, MapCoord mapCoord)
	:
	OObjectTitled(meshName, title),
	mapCoord(mapCoord)
{
	const RealCoord realCoord = mapCoord;
	node->setPosition(realCoord.x, heightOfLabel, realCoord.y);
	node->setVisible(false);
}

OObjectLabel::~OObjectLabel()
{
}

}