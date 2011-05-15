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
	public:
		Enti *enti;

	public:
		Unit(Enti *enti);
		virtual ~Unit() = 0;

		// Callbacks do nothing by default!
		virtual void OnTick(const float seconds) {}
		virtual void OnMoveStart() {}
		virtual void OnMove() {}
		virtual void OnMoveStop() {}

	private:
		Unit(const Unit &_c);
		Unit & operator =(const Unit &_c);

	};
}

#endif	/* _UNIT_H */

