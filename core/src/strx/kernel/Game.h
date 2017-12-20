#pragma once

#include <Strategix_fwd.h>

namespace strx
{
class Game : boost::noncopyable
{
public:
	virtual ~Game() = default;
	
	virtual void Start() = 0;
	virtual void PlayerAdded(Player* player) = 0;
};

}
