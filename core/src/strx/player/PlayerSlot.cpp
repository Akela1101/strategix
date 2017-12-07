#include <strx/player/Player.h>

#include "PlayerSlot.h"


namespace strx
{
PlayerSlot::PlayerSlot(Player* player) : player(player)
{
	player->SetSlot(this);
}

PlayerSlot::~PlayerSlot() = default;

const string& PlayerSlot::GetName() const { return player->GetName(); }

int PlayerSlot::GetId() const { return player->GetId(); }

PlayerType PlayerSlot::GetType() const { return player->GetType(); }

Map& PlayerSlot::GetMap() const { return player->GetMap(); }

}