#ifndef _FEATURE_H
#define    _FEATURE_H

#include "Strategix_Forward.h"


namespace strx
{
class Feature : boost::noncopyable
{
protected:
	Enti* enti; // Link to enti

public:
	Feature(Enti* enti) : enti(enti) {}
	virtual ~Feature() = default;
	
	virtual bool Tick(float seconds) = 0; // stop tick, if false.
	virtual void Stop() = 0;
};
}

#endif    /* _FEATURE_H */

