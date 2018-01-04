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

	static void SendMessageOne(s_p<Message> message);

protected:
	virtual void MessageReceived(s_p<Message> message) = 0;
};
}
