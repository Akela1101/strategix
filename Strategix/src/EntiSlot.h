/* 
 * File:   EntiSlot.h
 * Author: Akela1101
 *
 * Created on 17 Март 2011 г., 20:19
 */

#ifndef _ENTISLOT_H
#define	_ENTISLOT_H

#include "Interfaces.h"

#include "Strategix_Forward.h"


namespace Strategix
{
	class EntiSlot : public ITick, public IMove, public ICollect
	{
	public:
		Enti *enti;

	public:
		EntiSlot(Enti *enti);
		virtual ~EntiSlot() = 0;		

	private:
		EntiSlot(const EntiSlot &_c);
		EntiSlot & operator =(const EntiSlot &_c);
	};
}

#endif	/* _ENTISLOT_H */

