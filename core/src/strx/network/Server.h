#pragma once

#include <Strategix_fwd.h>
#include <nya/signal.hpp>


namespace strx
{
class Server : public nya::event_loop_holder<Server>
{
	Server() = delete;

public:
	static void Run(ushort port);
	static void Finish();	
};
}