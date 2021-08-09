#include "../../strx/Message.hpp"

#include "../../strx/Player.hpp"


namespace strx
{
const string& Player::GetName() const
{
	return playerMessage->name;
}

int Player::GetSpot() const
{
	return playerMessage->spot;
}

PlayerType Player::GetType() const
{
	return playerMessage->type;
}
}  // namespace strx
