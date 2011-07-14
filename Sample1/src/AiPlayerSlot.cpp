/* 
 * File:   AiPlayerSlot.cpp
 * Author: Akela1101
 * 
 * Created on 13 Июль 2011 г., 16:34
 */

#include "OObjectEntiSlot.h"
#include "OObjectResource.h"

#include <Strategix.h>
#include <sstream>

#include "AiPlayerSlot.h"


namespace Sample1
{
	using namespace std;
	using namespace Strategix;


void AiPlayerSlot::OnAddEnti(sh_p<Enti> enti)
{
	entiSlots.insert(make_pair(enti, sh_p<OObjectEntiSlot>(new OObjectEntiSlot(enti))));
}

void AiPlayerSlot::OnRemoveEnti(sh_p<Enti> enti)
{
	entiSlots.erase(entiSlots.find(enti));
}

}