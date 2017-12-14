#ifndef _FEATURE_H
#define    _FEATURE_H

#include "Strategix_Forward.h"


namespace strx
{
class Feature : boost::noncopyable
{
protected:
	Entity* entity; // Link to entity

public:
	Feature(Entity* entity) : entity(entity) {}
	virtual ~Feature() = default;
	
	virtual void Tick(float seconds) = 0; // stop tick, if false.
	virtual void Stop() = 0;
};
}

#endif    /* _FEATURE_H */

