#include <entity/EntiSlot.h>
#include <player/Player.h>

#include "PlayerSlot.h"


namespace strategix
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
	if (player) player->AddEnti(enti);
}

}