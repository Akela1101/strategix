#include <strx/player/Player.h>

#include "PlayerSlot.h"


namespace strx
{
PlayerSlot::PlayerSlot(Player* player) : player(player) {}

PlayerSlot::~PlayerSlot() = default;

const string& PlayerSlot::GetName() const { return player->GetName(); }

PlayerType PlayerSlot::GetType() const { return player->GetType(); }

}