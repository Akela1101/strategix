#pragma once

#include "../../strx/strx_fwd.hpp"


namespace strx
{
class Feature : boost::noncopyable
{
protected:
	EntityKernel* entity;  // Link to entity

public:
	Feature(EntityKernel* entity) : entity(entity) {}
	virtual ~Feature() = default;

	virtual void Tick(float seconds) = 0;
	virtual void Stop() {}
	virtual void Completed(bool done) {}
};
}  // namespace strx
