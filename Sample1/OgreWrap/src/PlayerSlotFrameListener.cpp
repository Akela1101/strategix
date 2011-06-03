/* 
 * File:   PlayerSlotFrameListener.cpp
 * Author: Akela1101
 * 
 * Created on 13 Январь 2011 г., 21:23
 */

#include "OObjectEntiSlot.h"
#include "OObjectResource.h"

#include <Strategix.h>
#include <sstream>

#include "PlayerSlotFrameListener.h"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

PlayerSlotFrameListener::PlayerSlotFrameListener(sh_p<Kernel> kernel, sh_p<MyGUI::Gui> myGUI)
	:
	kernel(kernel),
	myGUI(myGUI),
	resourcesText(myGUI->createWidget<MyGUI::StaticText>("StaticText", 10, 10, 300, 26, MyGUI::Align::Default, "Main"))
{
	foreach( sh_p<Player > &player, kernel->players )
	{
		// Assigning Human's callback as this
		//if( player->playerType == HUMAN )
			player->playerSlot = this;		
	}
}

bool PlayerSlotFrameListener::frameRenderingQueued(const FrameEvent &event)
{
	kernel->Tick(event.timeSinceLastFrame); // Time transmitting to Strategix
	return true;
}


void PlayerSlotFrameListener::OnAddEnti(Enti *enti)
{	
	entiSlots.push_back(sh_p<OObjectEntiSlot>(new OObjectEntiSlot(enti)));
}

void PlayerSlotFrameListener::OnAddMapResource(sh_p<MapResource> mapResource)
{
	resources.push_back(sh_p<OObjectResource>(new OObjectResource(mapResource)));
}

void PlayerSlotFrameListener::OnChangeResources(const Resources &newResources)
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