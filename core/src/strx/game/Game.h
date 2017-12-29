#pragma once

#include <Strategix_fwd.h>

namespace strx
{
using PlayersType = umap<string, u_p<Player>>;

class Game : boost::noncopyable
{
	PlayersType players;       /// players by name

public:
	virtual ~Game() = default;

	PlayersType& GetPlayers() { return players; }

	void AddPlayer(const PlayerMessage& playerMessage);
};

}
