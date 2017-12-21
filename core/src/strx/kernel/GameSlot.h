#pragma once

#include <Strategix_fwd.h>


namespace strx
{
class GameSlot : boost::noncopyable
{
	ResourceInfosType resourceInfos;
	
public:
	GameSlot();
	virtual ~GameSlot();
	virtual void PlayerAdded(Player* player) = 0;
};
}
