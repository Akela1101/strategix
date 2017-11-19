#ifndef _FEATURE_H
#define    _FEATURE_H

#include "common/Strategix_Forward.h"


namespace strategix
{
class Feature
{
protected:
	Enti* enti; // Link to enti

public:
	Feature(Enti* enti) : enti(enti) {}
	
	virtual ~Feature() = default;
	
	virtual bool Tick(float seconds) = 0; // stop tick, if false.
	virtual void Stop() = 0;

	Feature(const Feature& _c) = delete;
	Feature& operator=(const Feature& _c) = delete;
};
}

#endif    /* _FEATURE_H */

