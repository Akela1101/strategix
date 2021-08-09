#include "../../strx/Message.hpp"

#include "../../strx/PlayerSlot.hpp"


namespace strx
{
const string& PlayerSlot::GetName() const
{
	return playerMessage->name;
}

int PlayerSlot::GetSpot() const
{
	return playerMessage->spot;
}

PlayerType PlayerSlot::GetType() const
{
	return playerMessage->type;
}
}  // namespace strx
