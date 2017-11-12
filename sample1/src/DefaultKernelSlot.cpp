#include <DefaultPlayerSlot.h>
#include <MapLocal.h>
#include <Player.h>
#include <TechTree.h>

#include "DefaultKernelSlot.h"


namespace Sample1
{
using namespace Strategix;


DefaultKernelSlot::~DefaultKernelSlot() = default;

void DefaultKernelSlot::OnAddPlayer(Player* player)
{
	auto playerSlot = make_u<DefaultPlayerSlot>();
	player->SetSlot(playerSlot.get());
	
	playerSlots[player->GetName()] = move(playerSlot);
}
}
