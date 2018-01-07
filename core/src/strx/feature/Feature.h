#pragma once

#include "Strategix_fwd.h"


namespace strx
{
class Feature : boost::noncopyable
{
protected:
	Entity* entity; // Link to entity

public:
	Feature(Entity* entity) : entity(entity) {}
	virtual ~Feature() = default;

	virtual void Tick(float seconds) = 0;
	virtual void Stop() {}
	virtual void Completed(bool done) {}
};
}
