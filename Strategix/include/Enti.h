/* 
 * File:   Enti.h
 * Author: Akela1101
 *
 * Created on 4 Февраль 2011 г., 18:41
 */

#ifndef _ENTI_H
#define	_ENTI_H

class Enti
{
public:
	Enti();	
	virtual ~Enti();

private:
	Enti(const Enti &_c);
	Enti & operator =(const Enti &_c);
	inline void init(const Enti &_c);

};

#endif	/* _ENTI_H */

