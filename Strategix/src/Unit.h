/* 
 * File:   Unit.h
 * Author: Akela1101
 *
 * Created on 17 Март 2011 г., 20:19
 */

#ifndef _UNIT_H
#define	_UNIT_H

#include "Interfaces.h"


namespace Strategix
{
	class Enti;

	class Unit : public ITick, public IMove, public ICollect
	{
	public:
		Enti *enti;

	public:
		Unit(Enti *enti);
		virtual ~Unit() = 0;		

	private:
		Unit(const Unit &_c);
		Unit & operator =(const Unit &_c);
	};
}

#endif	/* _UNIT_H */

