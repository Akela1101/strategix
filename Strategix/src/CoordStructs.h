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
	template<typename T, typename Y>
	struct Coord
	{
		T x, y;

		Coord() {}		
		Coord(const Coord &_c) : x(_c.x), y(_c.y) {}
		Coord(const T x, const T y) : x(x), y(y) {}

		operator Coord<Y, T>() const
		{
			return Coord<Y, T>(x, y);
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

		Coord operator *(const float _v)
		{
			return Coord(_v * x, _v * y);
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

	typedef Coord<int, float> MapCoord; // used in Maps
	typedef Coord<float, int> RealCoord; // used in Enti and everywhere

#ifdef MSCC
	template<>
	MapCoord::operator RealCoord() const
	{
		return RealCoord(0.5 + x, 0.5 + y); // Center object in cell
	}
#else // GCC
	template<>
	MapCoord::operator RealCoord() const;
#endif

}

#endif	/* _COORDSTRUCTS_H */

