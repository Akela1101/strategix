/* 
 * File:   Ent.h
 * Author: Akela1101
 *
 * Created on 15 Январь 2011 г., 23:34
 */

#ifndef _ENT_H
#define	_ENT_H

class Ent
{
public:
	Ent();
	Ent(const Ent &_c);
	Ent & operator =(const Ent &_c);
	virtual ~Ent();
private:
	inline void init(const Ent &_c);

};

#endif	/* _ENT_H */

