/* 
 * File:   HumanPlayerSlot.cpp
 * Author: Akela1101
 * 
 * Created on 13 Январь 2011 г., 21:23
 */

#include "OObjectEntiSlot.h"
#include "OObjectResource.h"

#include <Strategix.h>
#include <sstream>

#include "HumanPlayerSlot.h"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;

HumanPlayerSlot::HumanPlayerSlot()
{
	// MyGUI
	myGUI.reset(new MyGUI::Gui());
	myGUI->initialise();
	myGUI->setVisiblePointer(false);

	// Resources text
	resourcesText = myGUI->createWidget<MyGUI::StaticText>("StaticText", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
}

HumanPlayerSlot::~HumanPlayerSlot()
{
	// MyGUI
	myGUI->shutdown();
	myGUI.reset();
}

void HumanPlayerSlot::OnAddEnti(Enti *enti)
{	
	entiSlots.push_back(sh_p<OObjectEntiSlot>(new OObjectEntiSlot(enti)));
}

void HumanPlayerSlot::OnAddMapResource(sh_p<MapResource> mapResource)
{
	resources.push_back(sh_p<OObjectResource>(new OObjectResource(mapResource)));
}

void HumanPlayerSlot::OnChangeResources(sh_p<Resources> newResources)
{
	string resourceCaption = "#FFFFFF"; // white
	foreach( const ResourceValueType pa, newResources->Get() )
	{
		resourceCaption += pa.first + ": ";

		std::stringstream ss; ss << pa.second;
		resourceCaption += ss.str() + "   ";
	}
	resourcesText->setCaption(resourceCaption);
}

}