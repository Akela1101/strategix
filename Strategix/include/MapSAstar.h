/* 
 * File:   MapSAstar.h
 * Author: Akela1101
 *
 * Created on 20 Апрель 2010 г., 9:14
 */

#ifndef _MAPSASTAR_H
#define	_MAPSASTAR_H

class MapSAstar
{
public:
	MapSAstar();
	MapSAstar(const MapSAstar &_c);
	MapSAstar & operator =(const MapSAstar &_c);
	virtual ~MapSAstar();
private:
	inline void init(const MapSAstar &_c);

};

#endif	/* _MAPSASTAR_H */

