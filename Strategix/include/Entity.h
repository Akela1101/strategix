/* 
 * File:   Entity.h
 * Author: Akela1101
 *
 * Created on 23 Июнь 2010 г., 16:05
 */

#ifndef _ENTITY_H
#define	_ENTITY_H


namespace Strategix
{
	using namespace std;

	class Entity
	{
	public:
		Entity();
		Entity(const Entity &_c);
		Entity & operator =(const Entity &_c);
		virtual ~Entity();
	private:
		inline void init(const Entity &_c);

	};
}

#endif	/* _ENTITY_H */

