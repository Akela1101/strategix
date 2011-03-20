/* 
 * File:   Unit.h
 * Author: Akela1101
 *
 * Created on 17 Март 2011 г., 20:19
 */

#ifndef _UNIT_H
#define	_UNIT_H

namespace Strategix
{
	class Enti;

	class Unit
	{
		Enti *enti; // const ?

	public:
		Unit(Enti *enti);
		virtual ~Unit() = 0;

		virtual void OnTick(float time) = 0;

	private:
		Unit(const Unit &_c);
		Unit & operator =(const Unit &_c);

	};
}

#endif	/* _UNIT_H */

