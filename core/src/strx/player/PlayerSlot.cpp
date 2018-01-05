#include <strx/kernel/Message.h>

#include "PlayerSlot.h"


namespace strx
{
PlayerSlot::PlayerSlot(s_p<PlayerMessage> playerMessage) : playerMessage(move(playerMessage)) {}

const string& PlayerSlot::GetName() const { return playerMessage->name; }

int PlayerSlot::GetSpot() const { return playerMessage->spot; }

PlayerType PlayerSlot::GetType() const { return playerMessage->type; }
}
