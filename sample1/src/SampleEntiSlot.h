#ifndef _SAMPLEENTISLOT_H
#define _SAMPLEENTISLOT_H

#include <EntiSlot.h>

namespace sample1
{
using namespace strategix;
class SampleEntiSlot : public EntiSlot
{
	using EntiSlot::EntiSlot;
	
public:
	void OnMove() override {}
};
}

#endif //_SAMPLEENTISLOT_H
