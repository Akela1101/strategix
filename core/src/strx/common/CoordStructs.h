#ifndef _COORDSTRUCTS_H
#define    _COORDSTRUCTS_H

#include <boost/operators.hpp>

namespace strx
{
template<typename T, typename Y>
struct Coord
		: boost::totally_ordered<Coord<T, Y>
		, boost::additive<Coord<T, Y>
		, boost::multiplicative<Coord<T, Y>, float>>>
{
	T x, y;
	
	Coord() {}
	Coord(T x, T y) : x(x), y(y) {}
	Coord(const Coord& other) = default;
	Coord& operator =(const Coord& other) = default;
	
	operator Coord<Y, T>() const { return Coord<Y, T>(x, y); }
	
	bool operator ==(const Coord& other) const { return x == other.x && y == other.y; }
	bool operator <(const Coord& other) const { return x != other.x ? x < other.x : y < other.y; }
	Coord& operator +=(const Coord& other) { x += other.x, y += other.y; return *this; }
	Coord& operator -=(const Coord& other) { x -= other.x, y -= other.y; return *this; }
	Coord& operator *=(float value) { x *= value, y *= value; return *this; }
	
	T Len() const { return x * x + y * y; }
	Coord Norm() const { float invLen = 1.0 / Len(); return Coord(x * invLen, y * invLen); }
};

using MapCoord  = Coord<int, float>; // used in Maps
using RealCoord = Coord<float, int>; // used in Enti and everywhere

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

namespace std
{
template<> struct hash<strx::MapCoord>
{
	static constexpr int shift = sizeof(size_t) * 8 / 2;
	
	size_t operator()(const strx::MapCoord& coord) const noexcept
	{
		return coord.x ^ ((size_t)coord.y << shift);
	}
};
}

#endif    /* _COORDSTRUCTS_H */

