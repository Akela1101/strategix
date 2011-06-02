/* 
 * File:   EntiSlot.cpp
 * Author: Akela1101
 * 
 * Created on 17 Март 2011 г., 20:19
 */

#include "Enti.h"

#include "EntiSlot.h"


namespace Strategix
{

EntiSlot::EntiSlot(Enti *enti) : enti(enti)
{
	enti->entiSlot = this;
}

EntiSlot::~EntiSlot()
{}

}
