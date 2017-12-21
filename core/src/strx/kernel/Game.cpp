#include <strx/kernel/Kernel.h>
#include <strx/player/Player.h>

#include "Game.h"

namespace strx
{
void Game::AddPlayer(u_p<Player> player)
{
	players.emplace(player->GetName(), move(player));
	//game->PlayerAdded(player);
}
}
