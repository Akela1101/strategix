#include <strx/entity/EntiSlot.h>
#include <strx/player/Player.h>

#include "PlayerSlot.h"


namespace strx
{
PlayerSlot::PlayerSlot(string name, PlayerType type, int playerNumber, string raceName)
		: name(move(name))
		, type(type)
		, playerNumber(playerNumber)
		, raceName(move(raceName))
{}

PlayerSlot::~PlayerSlot() = default;

void PlayerSlot::AddEnti(EntiSlot* enti)
{
	if (!player)
		nya_throw << "Add player to game before adding " << enti->GetName();
	
	player->AddEnti(enti);
}

}