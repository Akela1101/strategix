/* 
 * File:   MediatorFrameListener.cpp
 * Author: Akela1101
 * 
 * Created on 13 Январь 2011 г., 21:23
 */

#include "OObjectUnit.h"
#include "OObjectResource.h"

#include "EntiInfo.h"
#include "Enti.h"
#include "Player.h"
#include "Kernel.h"
#include "KernelBase.h"
#include "MapFull.h"
#include "MapResource.h"
#include "TechTree.h"
#include "StrategixError.h"

#include "MyGUI.h"

#include <OgreEntity.h>
#include <OgreNode.h>

#include <sstream>

#include "MediatorFrameListener.h"
#include "Nya.hpp"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

MediatorFrameListener::MediatorFrameListener(sh_p<Kernel> kernel, sh_p<MyGUI::Gui> myGUI)
	:
	kernel(kernel),
	myGUI(myGUI)
{
	resourcesText = myGUI->createWidget<MyGUI::StaticText>("StaticText", 10, 10, 300, 26, MyGUI::Align::Default, "Main");

	MapFull &mapFull = kernel->GetMap();

	// Do next stuff inside Kernel::Start() !!!!!!!!!!!!
	// but set mediator here.

	// Players' initialization
	foreach( sh_p<Player > &player, kernel->players )
	{
		// Assigning Human's callback as this
		//if( player->playerType == HUMAN )
			player->mediator = this;		

		// Getting Base Info
		const string baseName = player->techTree->mainBuildingName;
		sh_p<const EntiInfo> entityInfo = player->techTree->Node(baseName);
		// Getting Player's Initial Position
		const MapCoord &mapCoord = mapFull.GetInitialPostion(player->playerNumber);
		// Creating Base
		player->AddEnti(sh_p<Enti>(new Enti(entityInfo.get(), mapCoord)));
	}

	// Resources
	for( int i = 0; i < mapFull.GetWidth(); ++i )
	{
		for( int j = 0; j < mapFull.GetLength(); ++j )
		{
			sh_p<MapResource> mapResource = mapFull.GetCell(i, j).mapResource;
			if( mapResource )
			{
				const string meshName = KernelBase::GS().GetResourceInfo(mapResource->name).meshName;
				
				resources.push_back(sh_p<OObjectResource>(new OObjectResource(meshName, mapResource)));
			}
		}
	}

	// @#~
	kernel->players[0]->AddEnti(sh_p<Enti>(new Enti(&*kernel->players[0]->techTree->Node("Spher_Worker"), MapCoord(4, 16))));
	kernel->players[0]->AddEnti(sh_p<Enti>(new Enti(&*kernel->players[0]->techTree->Node("Spher_Worker"), MapCoord(6, 17))));
	kernel->players[0]->AddEnti(sh_p<Enti>(new Enti(&*kernel->players[0]->techTree->Node("Spher_Worker"), MapCoord(6, 16))));
	kernel->players[0]->AddEnti(sh_p<Enti>(new Enti(&*kernel->players[0]->techTree->Node("Spher_Worker"), MapCoord(4, 15))));
}

bool MediatorFrameListener::frameRenderingQueued(const FrameEvent &event)
{
	kernel->Tick(event.timeSinceLastFrame); // Time transmitting to Strategix
	return true;
}


void MediatorFrameListener::OnAddEnti(Enti *enti)
{
	sh_p<OObjectUnit> unit(new OObjectUnit(enti));
	units.push_back(unit);
}

void MediatorFrameListener::OnChangeResources(const Resources &newResources)
{
	string resourceCaption = "#FFFFFF";
	foreach( const ResourceInfos::value_type pa, KernelBase::GS().GetResourceInfos() )
	{
		resourceCaption += pa.first + ": ";

		std::stringstream ss; ss << newResources(pa.first);
		resourceCaption += ss.str() + "   ";
	}
	resourcesText->setCaption(resourceCaption);
}

}