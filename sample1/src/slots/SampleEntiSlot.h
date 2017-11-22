#ifndef _SAMPLEENTISLOT_H
#define _SAMPLEENTISLOT_H

#include <strx/entity/EntiSlot.h>

namespace sample1
{
using namespace strx;
class SampleEntiSlot : public EntiSlot
{
	using EntiSlot::EntiSlot;
	
public:
	void OnMove() override {}
};
}

#endif //_SAMPLEENTISLOT_H
