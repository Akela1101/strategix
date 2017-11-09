/* 
 * File:   Feature.h
 * Author: Akela1101
 *
 * Created on 23 Март 2011 г., 16:05
 */

#ifndef _FEATURE_H
#define    _FEATURE_H

#include "Strategix_Forward.h"


namespace Strategix
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

