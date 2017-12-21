#pragma once

#include <Strategix_fwd.h>
#include <nya/signal.hpp>

namespace strx
{
class Client : public nya::event_loop_holder<Client>
{
	Client() = delete;

public:
	static void StartSession();
	static void StopSession();
};
}
