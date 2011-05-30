/* 
 * File:   Mediator.h
 * Author: Akela1101
 *
 * Created on 17 Март 2011 г., 20:18
 */

#ifndef _MEDIATOR_H
#define	_MEDIATOR_H


namespace Strategix
{
	class Enti;
	class Resources;

	class Mediator
	{
	public:
		Mediator() {}
		virtual ~Mediator() {}
		
		virtual void OnAddEnti(Enti *enti) = 0;
		virtual void OnChangeResources(const Resources &newResources) = 0;

	private:
		Mediator(const Mediator &_c);
		Mediator & operator =(const Mediator &_c);
	};
}

#endif	/* _MEDIATOR_H */

