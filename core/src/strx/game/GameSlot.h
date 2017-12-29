#pragma once

#include <Strategix_fwd.h>

namespace strx
{
class GameSlot : boost::noncopyable
{
	friend class Client;

	ResourceInfosType resourceInfos;

public:
	GameSlot();
	virtual ~GameSlot();

protected:
	void SendOneMessage(s_p<Message> message);
	virtual void OnReceiveMessage(s_p<Message> message) = 0;
};
}
