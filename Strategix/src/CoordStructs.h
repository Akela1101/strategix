/* 
 * File:   CoordStructs.h
 * Author: Akela1101
 *
 * Created on 20 Март 2011 г., 12:05
 */

#ifndef _COORDSTRUCTS_H
#define	_COORDSTRUCTS_H


namespace Strategix
{
	template<typename T>
	struct Coord
	{
		T x, y;

		Coord() {}		
		Coord(const Coord &_c) : x(_c.x), y(_c.y) {}
		Coord(const T x, const T y) : x(x), y(y) {}

		template<typename Y>
		operator Coord<Y>() const
		{
			return Coord<Y>(x, y);
		}

		bool operator ==(const Coord &_r) const
		{
			return x == _r.x && y == _r.y;
		}

		bool operator !=(const Coord &_r) const
		{
			return x != _r.x || y != _r.y;
		}

		Coord operator +(const Coord &_r) const
		{			
			return Coord(x + _r.x, y + _r.y);
		}

		Coord operator -(const Coord &_r) const
		{			
			return Coord(x - _r.x, y - _r.y);
		}

		Coord& operator +=(const Coord &_r)
		{
			x += _r.x;
			y += _r.y;
			return this;
		}

		Coord& operator -=(const Coord &_r)
		{
			x -= _r.x;
			y -= _r.y;
			return this;
		}

		template<typename Y>
		Coord operator *(const Y _v)
		{
			return Coord(x * _v, y * _v);
		}

		T Len() const
		{
			return x*x + y*y;
		}

		Coord Norm() const
		{
			T invLen = 1.0 / Len();
			return Coord(x * invLen, y * invLen);
		}
	};

	typedef Coord<int> MapCoord; // used in Maps
	typedef Coord<float> RealCoord; // used in Enti and the game

	template<>
	template<>
	MapCoord::operator RealCoord() const;
}

#endif	/* _COORDSTRUCTS_H */

