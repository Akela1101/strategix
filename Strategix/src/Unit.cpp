/* 
 * File:   Unit.cpp
 * Author: Akela1101
 * 
 * Created on 17 Март 2011 г., 20:19
 */

#include "Enti.h"

#include "Unit.h"


namespace Strategix
{

Unit::Unit(Enti *enti) : enti(enti)
{
	enti->unit = this;
}

Unit::~Unit()
{
}

}
